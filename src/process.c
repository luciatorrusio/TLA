#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <tree_printing.h>
#include <process.h>
#include <project.h>
#include <translate.h>
#include <hashtable.h>

struct restorable_var_info {
	struct var_info * s;
	struct restorable_var_info * next;
};

struct node_list {
	nodeType * arg;
	struct node_list * next;
};

static char *types[] = {"img", "int", "string", "float"};

static void init_functions_h(void);
static void init_symbols_h(void);

static void add_fun_to_list(struct function_info * f);
static void pre_load_native_functions();

static void add_type_to_fun(struct function_info * f, nodeType * type_qualifier);
static void add_params_to_fun(struct function_info * f, nodeType * fun_declarator);
static void check_libraries(nodeType * t, bool * errored);

static void create_context();
static void delete_current_context();
static void add_var_to_list(struct var_info * sym);
static void add_restorable_var_to_list(struct restorable_var_info * rest);
static void add_symbol_to_current_context(typNodeType * type, idNodeType * id);
static void add_symbols_func_param(nodeType * t);
static void add_symbols_func(nodeType * t);
static void assert_return_stmts_type(nodeType * t, typNodeType * type, bool * errored);
static void assert_type_rec(nodeType * t, cTyp typ, bool * errored);
static void assert_type_arr(nodeType * init_list, cTyp typ, bool * errored);
static void assert_function_returns_type(nodeType * id, typNodeType * type, bool * errored);
static void assert_variable_type(nodeType * id, typNodeType * type, bool * errored);
static void assert_type(nodeType * t, typNodeType * type, bool * errored);
static void assert_variable_exists(nodeType * id, bool * errored);
static struct node_list * prepare_params(nodeType * args);
static void free_node_list(struct node_list * node_list);
static void assert_function_params_variable(identifierT id, typNodeType * type, struct node_list * args, bool * errored);
static void assert_function_params(identifierT id, paramNode * fun_param, struct node_list * args, int line, bool * errored);
static void assert_function_exists(nodeType * id, nodeType * args, bool * errored);
static int get_symbol_type(identifierT id, typNodeType * type);
static void check_types_rec(nodeType * t, bool * errored);
static void check_types(nodeType * t, bool * errored);

static void destroy_functions_h(void);
static void	destroy_symbols_h(void);

static void delete_allocated_functions(void);

// shorthand way to get the key from hashtable or defVal if not found
#define kh_get_val(kname, hash, key, defVal) ({k=kh_get(kname, hash, key);(k!=kh_end(hash)?kh_val(hash,k):defVal);})

// shorthand way to set value in hash with single line command.  Returns value
// returns 0=replaced existing item, 1=bucket empty (new key), 2-adding element previously deleted
#define kh_set(kname, hash, key, val) ({int ret; k = kh_put(kname, hash,key,&ret); kh_value(hash,k) = val; ret;})

#define kh_key_present(hash, key) (!(key == kh_end(hash)))

#define MAX_PARAMS_NATIVE 10

struct function_info_basic {
  typNodeType ret;
  
  char * id;

	bool p_variable;
	unsigned int p_amount;
	// list
	typNodeType p_params[MAX_PARAMS_NATIVE];
};

static struct function_info_basic native_funcs_basic[] = {
	{
		.ret = {imageTyp},
		.id = "collage",
		.p_variable = true,
		.p_amount = 1,
		.p_params = {
			{
				.t = imageTyp,
				.arr = true
			}
		}
	},
	{
		.ret = {imageTyp},
		.id = "gray_scale_image",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			}
		}
	},
	{
		.ret = {imageTyp},
		.id = "image_mirror",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = stringTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {imageTyp},
		.id = "invert_colors",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			}
		}
	},
	{
		.ret = {imageTyp},
		.id = "load_image",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = stringTyp,
				.arr = false
			}
		}
	},
	{
		.ret = {imageTyp},
		.id = "resize_image",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = floatTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {imageTyp},
		.id = "rotate_image",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {imageTyp},
		.id = "write_on_image",
		.p_variable = false,
		.p_amount = 8,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = stringTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = true
			},
			{
				.t = stringTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = true
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {imageTyp},
		.id = "crop_image",
		.p_variable = false,
		.p_amount = 5,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "save_image",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = stringTyp,
				.arr = false
			},
			{
				.t = imageTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "save_image_cmap",
		.p_variable = false,
		.p_amount = 3,
		.p_params = {
			{
				.t = stringTyp,
				.arr = false
			},
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = stringTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "show_image",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "show_image_cmap",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = imageTyp,
				.arr = false
			},
			{
				.t = stringTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {stringTyp},
		.id = "substring",
		.p_variable = false,
		.p_amount = 3,
		.p_params = {
			{
				.t = stringTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
			{
				.t = intTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "print",
		.p_variable = true,
		.p_amount = 0,
		.p_params = {}
	},
	{
		.ret = {intTyp},
		.id = "len",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = intTyp,
				.arr = true
			},
		}
	},
	{
		.ret = {floatTyp},
		.id = "pow",
		.p_variable = false,
		.p_amount = 2,
		.p_params = {
			{
				.t = floatTyp,
				.arr = false
			},
			{
				.t = floatTyp,
				.arr = false
			},
		}
	},
	{
		.ret = {intTyp},
		.id = "int",
		.p_variable = false,
		.p_amount = 1,
		.p_params = {
			{
				.t = floatTyp,
				.arr = false
			},
		}
	},
};

// Global list of all functions info allocated
static struct function_info * allocated_functions = NULL;

KHASH_MAP_INIT_STR(functions_table, struct function_info *);

khash_t(functions_table) * functions_h;

static void init_functions_h() {
	functions_h = kh_init(functions_table); // create a hashtable
}

static void add_fun_to_list(struct function_info * f) {
    struct function_info * l = allocated_functions;
    f->next = l;
    allocated_functions = f;
}

static void pre_load_native_functions() {
	khiter_t k;

	int cantFuncs = sizeof(native_funcs_basic)/sizeof(struct function_info_basic);

	for(int i = 0 ; i < cantFuncs ; i++) {
		struct function_info_basic * native = &native_funcs_basic[i];
		struct function_info * f = calloc(1, sizeof(struct function_info));

		f->ret = native->ret;
		strcpy(f->id, native->id);
		f->params.variable = native->p_variable;
		f->params.amount = native->p_amount;

		paramNode * prev = NULL;
		paramNode * curr = NULL;
		for (unsigned j = 0; j < f->params.amount; j++) {
			curr = calloc(1, sizeof(paramNode));

			if (prev == NULL) {
				f->params.params = curr;
			}
			else {
				prev->next = curr;
			}

			memcpy(&curr->p, &native->p_params[j], sizeof(typNodeType));

			prev = curr;
			curr = prev->next;
		}

		add_fun_to_list(f);

		kh_set(functions_table, functions_h, f->id, f);
	}
}

static void add_type_to_fun(struct function_info * f, nodeType * type_qualifier) {
	if (type_qualifier->type == typeTyp) {
		f->ret.t = type_qualifier->typ.t;
		f->ret.arr = type_qualifier->typ.arr;
	}
}

static paramNode * add_param_to_fun(struct function_info * f, nodeType * param_decl_list) {
	if (param_decl_list->type == typeOpr && param_decl_list->opr.oper == PARAM_DECL_LIST) {
		nodeType * decl_list = param_decl_list->opr.op[0];
		nodeType * decl = param_decl_list->opr.op[1];

		nodeType * type_qualifier = decl->opr.op[0];

		paramNode * n = add_param_to_fun(f, decl_list);
		
		paramNode * newNode = calloc(1, sizeof(paramNode));
		newNode->p.t = type_qualifier->typ.t;
		newNode->p.arr = type_qualifier->typ.arr;

		n->next = newNode;
		f->params.amount++;
		return n;
	}
	else {
		nodeType * type_qualifier = param_decl_list->opr.op[0];

		paramNode * newNode = calloc(1, sizeof(paramNode));
		newNode->p.t = type_qualifier->typ.t;
		newNode->p.arr = type_qualifier->typ.arr;

		f->params.amount++;
		return newNode;
	}
}

static void add_params_to_fun(struct function_info * f, nodeType * fun_declarator) {
	if (fun_declarator->type == typeOpr && fun_declarator->opr.oper == FUNC_DEC) {
		if (fun_declarator->opr.nops > 0) {
			f->params.amount = 0;
			f->params.variable = false;
			f->params.params = add_param_to_fun(f, fun_declarator->opr.op[0]);
		}
		else {
			f->params.amount = 0;
			f->params.variable = false;
			f->params.params = NULL;
		}
	}
}

static void check_libraries(nodeType * t, bool * errored) {
	if (t->type == typeOpr) {
		if (t->opr.oper == FUNC_DEF && t->opr.nops == 4) {
			khiter_t k;

			struct function_info * f = malloc(sizeof(struct function_info));
			memset(f, 0x0, sizeof(struct function_info));

			nodeType * type_qualifier = t->opr.op[0];
			nodeType * id = t->opr.op[1];
			nodeType * fun_declarator = t->opr.op[2];

			add_type_to_fun(f, type_qualifier);
			strcpy(f->id, id->ide.i);
			add_params_to_fun(f, fun_declarator);

			add_fun_to_list(f);

			k = kh_get(functions_table, functions_h, f->id);
   		if (kh_key_present(functions_h, k)) {
				*errored = true;
				fprintf(stderr, "Error: Function '%s' already exists (line %d)\n", f->id, id->line);
			}
			else {
				kh_set(functions_table, functions_h, f->id, f);
			}
		}
		else {
			for(unsigned int i = 0; i < t->opr.nops; i++) {
				check_libraries(t->opr.op[i], errored);
			}
		}
	}
}

// Global list of all symbols info allocated
static struct var_info * allocated_symbols = NULL;

// Current symbols used
struct sym_am {
	int amount;
	struct sym_am * next;
};

static struct sym_am * used_symbols_amounts;

// Symbols to be restored after current context finish
static struct restorable_var_info * to_restore_symbols = NULL;

static struct sym_am * to_restore_symbols_amounts;

KHASH_MAP_INIT_STR(symbols_table, struct var_info *);

khash_t(symbols_table) * symbols_h;

static void init_symbols_h() {
	symbols_h = kh_init(symbols_table); // create a hashtable
}

static void create_context() {
	struct sym_am * a = calloc(1, sizeof(struct sym_am));

	if (used_symbols_amounts != NULL) {
		a->next = used_symbols_amounts;
	}
	used_symbols_amounts = a;

	struct sym_am * r = calloc(1, sizeof(struct sym_am));

	if (to_restore_symbols_amounts != NULL) {
		r->next = to_restore_symbols_amounts;
	}
	to_restore_symbols_amounts = r;

}

static void delete_current_context() {
	khiter_t k;

	struct sym_am * used_amount = used_symbols_amounts;
	struct var_info * v_curr = allocated_symbols;
	struct var_info * v_prev = v_curr;

	if (used_amount != NULL) {

		while(used_amount->amount > 0 && v_prev != NULL) {
			v_curr = v_prev->next;
			k = kh_get(symbols_table, symbols_h, v_prev->id); // get the iterator
   		if (kh_key_present(symbols_h, k)) {  // if it is found
				kh_del(symbols_table, symbols_h, k);  // then delete it.
   		}
			free(v_prev);
			v_prev = v_curr;
			(used_amount->amount)--;
		}

		used_symbols_amounts = used_symbols_amounts->next;
		free(used_amount);
	}

	struct sym_am * to_restore_amount = to_restore_symbols_amounts;
	struct restorable_var_info * r_curr = to_restore_symbols;
	struct restorable_var_info * r_prev = r_curr;

	if (to_restore_amount != NULL) {

		while(to_restore_amount->amount > 0 && r_prev != NULL) {
			r_curr = r_prev->next;
			kh_set(symbols_table, symbols_h, r_prev->s->id, r_prev->s);
			free(r_prev);
			r_prev = r_curr;
			(to_restore_amount->amount)--;
		}

		to_restore_symbols_amounts = to_restore_symbols_amounts->next;
		free(to_restore_amount);
	}
}

static void add_var_to_list(struct var_info * sym) {
	struct var_info * l = allocated_symbols;
	sym->next = l;
	allocated_symbols = sym;
}

static void add_restorable_var_to_list(struct restorable_var_info * rest) {
	struct restorable_var_info * l = to_restore_symbols;
	rest->next = l;
	to_restore_symbols = rest;
}

static void add_symbol_to_current_context(typNodeType * type, idNodeType * id) {
	khiter_t k;

	struct var_info * new_symbol = calloc(1, sizeof(struct var_info));

	strcpy(new_symbol->id, id->i);
	new_symbol->type.t = type->t;
	new_symbol->type.arr = type->arr;

	add_var_to_list(new_symbol);

	struct sym_am * used_amount = used_symbols_amounts;

	if (used_amount != NULL) {
		(used_amount->amount)++;
	}

	k = kh_get(symbols_table, symbols_h, new_symbol->id);
	if (kh_key_present(symbols_h, k)) {  
		struct var_info * to_preserve = kh_val(symbols_h, k);
		struct restorable_var_info * rest = calloc(1, sizeof(struct restorable_var_info));
		rest->s = to_preserve;
		add_restorable_var_to_list(rest);
	}

	kh_set(symbols_table, symbols_h, new_symbol->id, new_symbol);

	fprintf(stderr, "ADDED SYMBOL ID: %s\n", new_symbol->id);
}

static void add_symbols_func_param(nodeType * t) {
	nodeType * type_qualifier;
	nodeType * id;

	if (t->type == typeOpr && t->opr.oper == PARAM_DECL_LIST) {
		nodeType * decl_list = t->opr.op[0];
		nodeType * decl = t->opr.op[1];

		add_symbols_func_param(decl_list);

		type_qualifier = decl->opr.op[0];
		id = decl->opr.op[1];
	}
	else {
		type_qualifier = t->opr.op[0];
		id = t->opr.op[1];
	}

	add_symbol_to_current_context(&type_qualifier->typ, &id->ide);

}

static void add_symbols_func(nodeType * t) {
	if (t->opr.nops > 0) {
		nodeType * param_decl_list = t->opr.op[0];
		add_symbols_func_param(param_decl_list);
	}
}

static void assert_return_stmts_type(nodeType * t, typNodeType * type, bool * errored) {
	if (t == NULL) {
		return;
	}

	if (t->type == typeOpr) {
		if (t->opr.oper == RET) {
			assert_type(t->opr.op[0], type, errored);
		}
		else {
			for (unsigned int i = 0; i < t->opr.nops; i++) {
				assert_return_stmts_type(t->opr.op[i], type, errored);
			}
		}
	}
}

static void assert_type_arr(nodeType * init_list, cTyp typ, bool * errored) {
	if(init_list == NULL) {
		return;
	}

	typNodeType type;
	type.t = typ;
	type.arr = false;

	if (init_list->type == typeOpr && init_list->opr.oper == INIT_LIST && init_list->opr.nops == 2) {
	 	nodeType * initializer_list = init_list->opr.op[0];
	 	nodeType * exp = init_list->opr.op[1];

		assert_type_arr(initializer_list, typ, errored);
		assert_type(exp, &type, errored);
	}
	else {
		assert_type(init_list, &type, errored);
	}
}

static void assert_function_returns_type(nodeType * id, typNodeType * type, bool * errored) {
	khiter_t k;

	struct function_info * f = kh_get_val(functions_table, functions_h, id->ide.i, NULL);
	if (f != NULL) {
		if (type->t != f->ret.t || type->arr != f->ret.arr) {
			*errored = true;
			fprintf(stderr, "Error: Expected %s%s, but found function '%s' that returns type %s%s\n", types[type->t], type->arr ? "[]":"", id->ide.i, types[f->ret.t], f->ret.arr ? "[]":"");
		}
	}
	else {
		// Later this will be marked as an error
	}
}

static void assert_variable_type(nodeType * id, typNodeType * type, bool * errored) {
	khiter_t k;

	struct var_info * v = kh_get_val(symbols_table, symbols_h, id->ide.i, NULL);
	if (v != NULL) {
		if (type->t != v->type.t || type->arr != v->type.arr) {
			*errored = true;
			fprintf(stderr, "Error: Expected %s%s, but found variable '%s' of type %s%s\n", types[type->t], type->arr ? "[]":"", id->ide.i, types[v->type.t], v->type.arr ? "[]":"");
		}
	}
	else {
		// Later this will be marked as an error
	}
}

static void assert_type_rec(nodeType * t, cTyp typ, bool * errored) {
	khiter_t k;
	struct var_info * v;
	struct function_info * f;
	unsigned int i;
	
	if (t == NULL) {
		return;
	}

	switch(t->type) {
		case typeOpr:
			switch(t->opr.oper) {
				case CONST_EXP_C:
					assert_type_rec(t->opr.op[0], typ, errored);
					break;
				case CONST_EXP_N:
					if (typ != stringTyp) {
						*errored = true;
						fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[stringTyp], t->line);
					}
					else {
						assert_type_rec(t->opr.op[0], typ, errored);
					}
					break;
				case LOG_OR_EXP:
				case LOG_AND_EXP:
				case OR_EXP:
				case EXCL_OR_EXP:
				case AND_EXP:
				case EQU_EXP:
				case REL_EXP:
				case SHI_EXP:
					if (typ != intTyp) {
						*errored = true;
						fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[intTyp], t->line);
					}
					break;
				case ADD_EXP:
					if (typ != floatTyp && typ != intTyp) {
						*errored = true;
						fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[intTyp], t->line);
					}
					break;
				case MULT_EXP:
					if ((t->opr.op[1]->mop.op == DIV || t->opr.op[1]->mop.op == AST) && typ != floatTyp && typ != intTyp) {
						*errored = true;
						fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[floatTyp], t->line);
					}
					else if (t->opr.op[1]->mop.op == MOD && typ != intTyp) {
						*errored = true;
						fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[intTyp], t->line);
					}
					break;
				case UNARY_EXP_OP:
					switch(t->opr.op[1]->mop.op) {
						case MNS:
						case NEG:
							if (typ != floatTyp && typ != intTyp) {
								*errored = true;
								fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[floatTyp], t->line);
							}
							break;
						case TIL:
							if (typ != intTyp) {
								*errored = true;
								fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[intTyp], t->line);
							}
							break;
						default:
							break;
					}
					break;

				// array
				case ARR_EXP:
					v = kh_get_val(symbols_table, symbols_h, t->ide.i, NULL);
					if (v != NULL) {
						if (!v->type.arr || v->type.t != typ) {
							*errored = true;
							fprintf(stderr, "Error: Expected %s, but found variable '%s' of type %s%s (line %d)\n", types[typ], t->ide.i, types[v->type.t], v->type.arr ? "[]":"", t->line);
						}
					}
					break;

				// check function return type (types are checked separately)
				case POST_EXP:
					f = kh_get_val(functions_table, functions_h, t->opr.op[0]->ide.i, NULL);
					if (f != NULL) {
						if (f->ret.arr || f->ret.t != typ) {
							*errored = true;
							fprintf(stderr, "Error: Expected %s, but found functions '%s' that returns type %s%s (line %d)\n", types[typ], t->ide.i, types[f->ret.t], f->ret.arr ? "[]":"", t->line);
						}
					}
					break;

				// array right val
				case NON_OP:
					*errored = true;
					fprintf(stderr, "Error: Expected %s, but found array (line %d)\n", types[typ], t->line);
					break;
				default:
					for (i = 0; i < t->opr.nops; i++) {
						assert_type_rec(t->opr.op[i], typ, errored);
					}
					break;
			}
			break;
		case typeStr:
			if (typ != stringTyp) {
				*errored = true;
				fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[stringTyp], t->line);
			}
			break;
		case typeFco:
			if (typ != floatTyp) {
				*errored = true;
				fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[floatTyp], t->line);
			}
			break;
		case typeCon:
			if (typ != floatTyp && typ != intTyp) {
				*errored = true;
				fprintf(stderr, "Error: Expected %s, but found %s (line %d)\n", types[typ], types[intTyp], t->line);
			}
			break;
		case typeId:
			v = kh_get_val(symbols_table, symbols_h, t->ide.i, NULL);
			if (v != NULL) {
				if (v->type.arr || v->type.t != typ) {
					*errored = true;
					fprintf(stderr, "Error: Expected %s, but found variable '%s' of type %s%s (line %d)\n", types[typ], t->ide.i, types[v->type.t], v->type.arr ? "[]":"", t->line);
				}
			}
			else {
				// Later this will be marked as an error
			}
			break;
		default:
			break;
	}
}

static void assert_type(nodeType * t, typNodeType * type, bool * errored) {
	fprintf(stderr, "ASSERTING FOR TYPE: %s%s\n", types[type->t], type->arr ? "[]":"");

	// Check every node asserting type
	if (type->arr) {
		if (t->type == typeOpr && t->opr.oper == CONST_EXP_N && t->opr.op[0]->opr.oper == NON_OP) {
			assert_type_arr(t->opr.op[0]->opr.op[0], type->t, errored);
		}
		else if (t->type == typeOpr && t->opr.oper == CONST_EXP_C) {
			if (t->opr.op[0]->opr.oper == POST_EXP && t->opr.op[0]->opr.nops == 2) {
				assert_function_returns_type(t->opr.op[0]->opr.op[0], type, errored);
			}
			else if (t->opr.op[0]->type == typeId) {
				assert_variable_type(t->opr.op[0], type, errored);
			}
			else {
				*errored = true;
				fprintf(stderr, "Error: Expected array declaration (line %d)\n", t->line);
			}
		}
		else {
			*errored = true;
			fprintf(stderr, "Error: Expected array declaration (line %d)\n", t->line);
		}
	}
	else {
		assert_type_rec(t, type->t, errored);
	}
}

static void assert_variable_exists(nodeType * id, bool * errored) {
	khiter_t k;

	struct var_info * v = kh_get_val(symbols_table, symbols_h, id->ide.i, NULL);
	if (v == NULL) {
		*errored = true;
		fprintf(stderr, "Error: Variable '%s' undeclared (line %d)\n", id->ide.i, id->line);
	}
}

static struct node_list * prepare_params(nodeType * args) {
	if(args == NULL) {
		return NULL;
	}
	
	if(args->type == typeOpr && args->opr.oper == ARG_EXP_LIST && args->opr.nops == 2) {
		nodeType * list = args->opr.op[0];
		nodeType * terminal = args->opr.op[1];

		struct node_list * ret = prepare_params(list);
		
		struct node_list * new_node = calloc(1, sizeof(struct node_list));
		new_node->arg = terminal;
		return ret;
	}
	else {
		struct node_list * new_node = calloc(1, sizeof(struct node_list));
		new_node->arg = args;
		return new_node;
	}
}

static void free_node_list(struct node_list * node_list) {
	struct node_list * curr = node_list;
	struct node_list * prev = curr;

	while(prev != NULL) {
		curr = prev->next;
		free(prev);
		prev = curr;
	}
}

static void assert_function_params_variable(identifierT id, typNodeType * type, struct node_list * args, bool * errored) {
	fprintf(stderr, "ASSERTING ARGS FROM FUNCTION: %s\n", id);
	
	if(args == NULL) return;
	
	assert_type(args->arg, type, errored);
	if(!errored) {
		assert_function_params_variable(id, type, args->next, errored);
	}
}

static void assert_function_params(identifierT id, paramNode * fun_param, struct node_list * args, int line, bool * errored) {
	fprintf(stderr, "ASSERTING ARGS FROM FUNCTION: %s\n", id);

	if(fun_param == NULL && args != NULL) {
		*errored = true;
		fprintf(stderr, "Error: No argument expected in function '%s' and received %s%s (line %d)\n", id, types[args->arg->typ.t], args->arg->typ.arr ? "[]":"",args->arg->line);
		return;
	}

	if(fun_param != NULL && args == NULL) {
		*errored = true;
		fprintf(stderr, "Error: %s%s expected in function '%s' and received none (line %d)\n", types[fun_param->p.t], fun_param->p.arr ? "[]":"", id, line);
		return;
	}
	
	if(fun_param == NULL && args == NULL) return;

	assert_type(args->arg, &fun_param->p, errored);
	if(!errored) {
		assert_function_params(id, fun_param->next, args->next, args->arg->line, errored);
	}
}

static void assert_function_exists(nodeType * id, nodeType * args, bool * errored) {
	fprintf(stderr, "ASSERTING FUNCTION '%s' EXISTS\n", id->ide.i);
	khiter_t k;

	struct function_info * s = kh_get_val(functions_table, functions_h, id->ide.i, NULL);
	if (s != NULL) {
		if (strcmp(id->ide.i, "print") == 0) {
			return;
		}

		if (s->params.variable) {
			typNodeType type;
			type.arr = s->params.params->p.arr;
			type.t = s->params.params->p.t;
			assert_function_params_variable(id->ide.i, &type, prepare_params(args), errored);
		}
		assert_function_params(id->ide.i, s->params.params, prepare_params(args), id->line, errored);
	}
	else {
		*errored = true;
		fprintf(stderr, "Error: Undeclared function '%s' (line %d)\n", id->ide.i, id->line);
	}
}

static int get_symbol_type(identifierT id, typNodeType * type) {
	khiter_t k;

	struct var_info * s = kh_get_val(symbols_table, symbols_h, id, NULL);
	if (s != NULL) {
		type->t = s->type.t;
		type->arr = s->type.arr;
		return 0;
	}
	else {
		return 1;
	}
}

/*
	-- CHECK OPERATIONS --

	logical_or_exp				
							: logical_and_exp             				{$$ = $1;}
							| logical_or_exp or_const logical_and_exp	{$$ = opr(LOG_OR_EXP, 3, $1, mop(LOG_OR), $3);} // Check inclusive_or_exp and logical_and_exp are int
							;
	logical_and_exp				
								: inclusive_or_exp          					{$$ = $1;}
								| logical_and_exp and_const inclusive_or_exp	{$$ = opr(LOG_AND_EXP, 3, $1, mop(LOG_AND), $3);} // Check logical_and_exp and inclusive_or_exp are int
								;
	inclusive_or_exp			
								: exclusive_or_exp										{$$ = $1;}
								| inclusive_or_exp '|' exclusive_or_exp	{$$ = opr(OR_EXP, 3, $1, mop(OR), $3);} // Check inclusive_or_exp and exclusive_or_exp are int
								;
	exclusive_or_exp			
								: and_exp															{$$ = $1;}
								| exclusive_or_exp '^' and_exp				{$$ = opr(EXCL_OR_EXP, 3, $1, mop(EXCL_OR), $3);} // Check exclusive_or_exp and and_exp are int
								;
	and_exp						
								: equality_exp												{$$ = $1;}
								| and_exp '&' equality_exp 						{$$ = opr(AND_EXP, 3, $1, mop(AND), $3);} // Check and_exp and equality_exp are int
								;
	equality_exp				
								: relational_exp											{$$ = $1;}
								| equality_exp eq_const relational_exp	{$$=opr(EQU_EXP, 3, $1, mop($2), $3);} // Check equality_exp and relational_exp are int/float (in case of variables) // Could be more.. but not for now
								; 
	relational_exp				
								: shift_exp									            {$$ = $1;}
								| relational_exp '<' shift_exp          {$$ = opr(REL_EXP, 3, $1, mop(L_THAN), $3 );} // Check relational_exp and shift_exp are int/float (in case of variables)
								| relational_exp '>' shift_exp          {$$ = opr(REL_EXP, 3, $1, mop(G_THAN), $3 );} // Check relational_exp and shift_exp are int/float (in case of variables)
								| relational_exp rel_const shift_exp    {$$ = opr(REL_EXP, 3, $1, mop($2) , $3);} // Check relational_exp and shift_exp are int/float (in case of variables)
								;
	shift_exp			
								: additive_exp													{$$ = $1;}
								| shift_exp shift_const additive_exp	{$$ = opr(SHI_EXP, 3, $1, mop($2), $3);} // Check shift_exp and additive_exp are int
								;
	additive_exp				
								: mult_exp														{$$ = $1;}
								| additive_exp '+' mult_exp           {$$ = opr(ADD_EXP, 3, $1, mop(PLS), $3);} // Check additive_exp and mult_exp are int/float (in case of variables)
								| additive_exp '-' mult_exp           {$$ = opr(ADD_EXP, 3, $1, mop(MNS), $3);} // Check additive_exp and mult_exp are int/float (in case of variables)
								;
	mult_exp					
								: unary_exp														{$$ = $1;}
								| mult_exp '*' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(AST), $3);} // Check mult_exp and unary_exp are int/float (in case of variables)
								| mult_exp '/' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(DIV), $3);} // Check mult_exp and unary_exp are int/float (in case of variables)
								| mult_exp '%' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(MOD), $3);} // Check mult_exp and unary_exp are int
								;
	unary_exp			
								: postfix_exp													{$$ = $1;}
								| unary_operator unary_exp						{$$ = opr(UNARY_EXP_OP, 2, $1, $2);}  // Check unary_exp is int
								;
	unary_operator				
								: '&' 																{$$ = mop(AMP);}
								| '-'                                 {$$ = mop(MNS);}
								| '~'                                 {$$ = mop(TIL);}
								| '!' 				                        {$$ = mop(NEG);}
								;

	arr_exp
							: id '[' conditional_exp ']' 					{$$ = opr(ARR_EXP, 2, ide($1), $3);} // Check conditional is int
							;

	-- Check functions params --
	postfix_exp					
							: primary_exp 		          					{$$ = $1;}			
							| arr_exp															{$$ = opr(POST_EXP, 1, $1);}
							| id '(' argument_exp_list ')'				{$$ = opr(POST_EXP, 2, ide($1), $3);} // Check id function params match
							|	id '(' ')'													{$$ = opr(POST_EXP, 2, ide($1), NULL);} // Check id function params match
							;							
*/
static void check_types_rec(nodeType * t, bool * errored) {
	if (t == NULL) {
		return;
	}
	
	unsigned int i;
	int res;
	typNodeType type;
	
	if (t->type == typeOpr) {
		switch(t->opr.oper) {
			
			// Context creators
			case FUNC_DEF:
				if (t->opr.op[3]->opr.nops > 0) {
					fprintf(stderr, "BUILDING FUNCTION CONTEXT\n");
					create_context();
					add_symbols_func(t->opr.op[2]);
					assert_return_stmts_type(t->opr.op[3]->opr.op[0], &(t->opr.op[0]->typ), errored);
					check_types_rec(t->opr.op[3]->opr.op[0], errored);
					delete_current_context();
				}
				break;
			case COMP_STAT:
				fprintf(stderr, "BUILDING COMPOUND STAT CONTEXT\n");
				if (t->opr.nops > 0) {
				 	create_context();
					check_types_rec(t->opr.op[0], errored);
					delete_current_context();
				}
				break;

			// Declarators
			case DECL:
				fprintf(stderr, "ADDING VARIABLES AND CHECKING - DECL FOUND\n");
				add_symbol_to_current_context(&(t->opr.op[0]->typ), &(t->opr.op[1]->opr.op[0]->ide));
				if (t->opr.op[1]->opr.op[1] != NULL) {
					assert_type(t->opr.op[1]->opr.op[1], &(t->opr.op[0]->typ), errored);
					check_types_rec(t->opr.op[1]->opr.op[1], errored);
				}
				break;

			// Assignments
			case ASS_EXP:
				if (t->opr.op[1] == NULL) { // '='
					fprintf(stderr, "ASSIGNMENT TO VARIABLE (=): %s\n", t->opr.op[0]->ide.i);
					res = get_symbol_type(t->opr.op[0]->ide.i, &type);
					if (res == 0) {
						assert_type(t->opr.op[2], &type, errored);
						check_types_rec(t->opr.op[2], errored);
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
					}
				}
				else if (t->opr.op[2] != NULL) { // '+=' | '-=' | '/=' | '>>=' | '<<=' | '*=' | '%='
					fprintf(stderr, "ASSIGNMENT TO VARIABLE (+=|-=|/=|>>=|<<=|*=|%%=): %s\n", t->opr.op[0]->ide.i);
					res = get_symbol_type(t->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (t->opr.op[1]->mop.op == ASS_R_SHIFT || t->opr.op[1]->mop.op == ASS_L_SHIFT || t->opr.op[1]->mop.op == ASS_MOD ) {
							if (type.t != intTyp) {
								*errored = true;
								fprintf(stderr, "Error: Variable '%s' must be int (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
							}
							type.t = intTyp;
							assert_type(t->opr.op[2], &type, errored);
							check_types_rec(t->opr.op[2], errored);
						}
						else {
							if (type.t == floatTyp || type.t == intTyp) {
								type.t = floatTyp;
								assert_type(t->opr.op[2], &type, errored);
								check_types_rec(t->opr.op[2], errored);
							}
							else {
								*errored = true;
								fprintf(stderr, "Error: Variable '%s' must be int/float (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
							}
						}
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
					}
				}
				else { // '++' | '--'
					res = get_symbol_type(t->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (type.t != floatTyp || type.t != intTyp) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be int/float (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
						}
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->ide.i, t->opr.op[0]->line);
					}
				}
				break;
			case ASS_EXP_A:
				if (t->opr.op[1] == NULL) { // '='
					fprintf(stderr, "ASSIGNMENT TO ARR VARIABLE (=): %s\n", t->opr.op[0]->opr.op[0]->ide.i);
					res = get_symbol_type(t->opr.op[0]->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (!type.arr) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be an array (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
						}
						type.arr = false;
						assert_type(t->opr.op[2], &type, errored);
						check_types_rec(t->opr.op[2], errored);
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
					}
				}
				else if (t->opr.op[2] != NULL) { // '+=' | '-=' | '/=' | '>>=' | '<<=' | '*=' | '%='
					fprintf(stderr, "ASSIGNMENT TO ARR VARIABLE (+=|-=|/=|>>=|<<=|*=|%%=): %s\n", t->opr.op[0]->opr.op[0]->ide.i);
					res = get_symbol_type(t->opr.op[0]->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (!type.arr) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be an array (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
						}
						if (t->opr.op[1]->mop.op == ASS_R_SHIFT || t->opr.op[1]->mop.op == ASS_L_SHIFT || t->opr.op[1]->mop.op == ASS_MOD ) {
							if (type.t != intTyp) {
								*errored = true;
								fprintf(stderr, "Error: Variable '%s' must be int[] (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
							}
							type.arr = false;
							type.t = intTyp;
							assert_type(t->opr.op[2], &type, errored);
							check_types_rec(t->opr.op[2], errored);
						}
						else {
							if (type.t == floatTyp || type.t == intTyp) {
								type.arr = false;
								type.t = floatTyp;
								assert_type(t->opr.op[2], &type, errored);
								check_types_rec(t->opr.op[2], errored);
							}
							else {
								*errored = true;
								fprintf(stderr, "Error: Variable '%s' must be int[]/float[] (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
							}
						}
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
					}
				}
				else { // '++' | '--'
					fprintf(stderr, "ASSIGNMENT TO ARR VARIABLE (++|--): %s\n", t->opr.op[0]->opr.op[0]->ide.i);
					res = get_symbol_type(t->opr.op[0]->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (!type.arr) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be an array (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
						}
						if (type.t != floatTyp || type.t != intTyp) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be int[]/float[] (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
						}
					}
					else {
						*errored = true;
						fprintf(stderr, "Error: Undeclared variable '%s' (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
					}
				}

				// check [ num ] is int
				type.t = intTyp;
				type.arr = false;
				assert_type(t->opr.op[0]->opr.op[1], &type, errored);
				check_types_rec(t->opr.op[0]->opr.op[1], errored);
				break;

			// Other checks
			case LOG_OR_EXP:
			case LOG_AND_EXP:
			case OR_EXP:
			case EXCL_OR_EXP:
			case AND_EXP:
				fprintf(stderr, "CHECKING INT_EXP\n");
				type.arr = false;
				type.t = intTyp;
				assert_type(t->opr.op[0], &type, errored);
				check_types_rec(t->opr.op[0], errored);
				assert_type(t->opr.op[2], &type, errored);
				check_types_rec(t->opr.op[2], errored);
				break;
			case MULT_EXP:
				if(t->opr.oper == MULT_EXP && (t->opr.op[1]->mop.op == DIV || t->opr.op[1]->mop.op == MOD)) {
					fprintf(stderr, "CHECKING INT_EXP\n");
					type.arr = false;
					type.t = intTyp;
				}
				else {
					fprintf(stderr, "CHECKING FLOAT_EXP\n");
					type.arr = false;
					type.t = floatTyp;
				}
				assert_type(t->opr.op[0], &type, errored);
				check_types_rec(t->opr.op[0], errored);
				assert_type(t->opr.op[2], &type, errored);
				check_types_rec(t->opr.op[2], errored);
				break;
			case EQU_EXP:
			case REL_EXP:
			case SHI_EXP:
			case ADD_EXP:
				fprintf(stderr, "CHECKING FLOAT_EXP\n");
				type.arr = false;
				type.t = floatTyp;
				assert_type(t->opr.op[0], &type, errored);
				check_types_rec(t->opr.op[0], errored);
				assert_type(t->opr.op[2], &type, errored);
				check_types_rec(t->opr.op[2], errored);
				break;
			case UNARY_EXP_OP:
				fprintf(stderr, "CHECKING UNARY_INT_EXP\n");
				type.arr = false;
				switch(t->opr.op[1]->mop.op) {
					case MNS:
					case NEG:
						type.t = floatTyp;
						assert_type(t->opr.op[0], &type, errored);
						check_types_rec(t->opr.op[0], errored);
						break;
					case TIL:
						type.t = intTyp;
						assert_type(t->opr.op[0], &type, errored);
						check_types_rec(t->opr.op[0], errored);
						break;
					default:
						break;
				}
				break;

			// check function exist
			case POST_EXP:
				fprintf(stderr, "CHECKING POST_EXP\n");
				if (t->opr.nops == 1) {
					res = get_symbol_type(t->opr.op[0]->opr.op[0]->ide.i, &type);
					if (res == 0) {
						if (!type.arr) {
							*errored = true;
							fprintf(stderr, "Error: Variable '%s' must be an array (line %d)\n", t->opr.op[0]->opr.op[0]->ide.i, t->opr.op[0]->opr.op[0]->line);
						}
					}
				}
				else {
					fprintf(stderr, "POST_EXP --> ASSERTING FUNCTION '%s' EXISTS\n", t->opr.op[0]->ide.i);
					assert_function_exists(t->opr.op[0], t->opr.op[1], errored);
					check_types_rec(t->opr.op[1], errored);
				}
				break;
			default:
				for (i = 0; i < t->opr.nops; i++) {
					check_types_rec(t->opr.op[i], errored);
				}
				break;
		}
	}
	else if (t->type == typeId) {
		assert_variable_exists(t, errored);
	}
}

static void check_types(nodeType * t, bool * errored) {
	check_types_rec(t, errored);
}

static void destroy_functions_h(void) {
	kh_destroy(functions_table, functions_h);
}

static void	destroy_symbols_h(void) {
	kh_destroy(symbols_table, symbols_h);
}

static void delete_allocated_functions(void) {
	struct function_info * curr = allocated_functions;
	struct function_info * prev = curr;
	while (prev != NULL) {
		curr = prev->next;
		if (prev != NULL) {
			if (prev->params.amount > 0 && prev->params.params != NULL) {
				paramNode * n_curr = prev->params.params;
				paramNode * n_prev = n_curr;

				while (n_prev != NULL) {
					n_curr = n_prev->next;
					free(n_prev);
					n_prev = n_curr;
				}
			}
			free(prev);
		}
		prev = curr;
	}
}

void process_tree(nodeType * root, bool * success) {
	prefix_print(root, 0);

	bool errored = false;

	init_functions_h();
	pre_load_native_functions();

	check_libraries(root, &errored);

	if (errored) {
		*success = false;
		fprintf(stderr, "Clashing Functions Conflict\n");
		return;
	}

	init_symbols_h();
	check_types(root, &errored);

	if (errored) {
		*success = false;
		fprintf(stderr, "Type Conflict\n");
		return;
	}

	translate_to_python(root);

	destroy_functions_h();
	destroy_symbols_h();

	delete_allocated_functions();
}