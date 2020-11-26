#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <tree_printing.h>
#include <process.h>
#include <project.h>
#include <translate.h>
#include <hashtable.h>

static void init_functions_h(void);
static void init_symbols_h(void);

static void add_fun_to_list(struct function_info * f);
static void pre_load_native_functions();

static void add_type_to_fun(struct function_info * f, nodeType * type_qualifier);
static void add_params_to_fun(struct function_info * f, nodeType * fun_declarator);
static void check_libraries(nodeType * t);

static void check_types_rec(nodeType * t, bool * checked);
static void check_types(nodeType * t, bool * checked);

static void destroy_functions_h(void);
static void	destroy_symbols_h(void);

static void delete_allocated_functions(void);
static void delete_allocated_symbols(void);

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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = imageTyp,
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
		.ret = intTyp,
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
		.ret = intTyp,
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
		.ret = intTyp,
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
		.ret = intTyp,
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
    allocated_functions = f->next;
}

static void pre_load_native_functions() {
	int ret, is_missing;
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

static void check_libraries(nodeType * t) {
	if (t->type == typeOpr) {
		if (t->opr.oper == FUNC_DEF && t->opr.nops == 4) {
			int ret, is_missing;
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

			printf("FUNCTION ID: %s\n", f->id);

			kh_set(functions_table, functions_h, f->id, f);
		}
		else {
			for(unsigned int i = 0; i < t->opr.nops; i++) {
				check_libraries(t->opr.op[i]);
			}
		}
	}
}

// Global list of all symbols info allocated
static struct var_info * allocated_symbols = NULL;

// Current symbols used
static struct var_info * current_symbols = NULL;

// Symbols to be restored after current context finish
static struct var_info * to_restore_symbols = NULL;

static void init_symbols_h() {
	functions_h = kh_init(functions_table); // create a hashtable
}

KHASH_MAP_INIT_STR(symbols_table, struct var_info *);

khash_t(symbols_table) * symbols_h;

static void check_types_rec(nodeType * t, bool * checked) {
	int ret, is_missing;
	khiter_t k;


}

static void check_types(nodeType * t, bool * checked) {
	check_types_rec(t, checked);
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
				free(prev->params.params);
			}
			free(prev);
		}
		prev = curr;
	}
}

static void delete_allocated_symbols(void) {
	struct var_info * curr = allocated_symbols;
	struct var_info * prev = curr;
	while (prev != NULL) {
		curr = prev->next;
		if (prev != NULL) {
			free(prev);
		}
		prev = curr;
	}
}

void process_tree(nodeType * root, bool * success) {
	prefix_print(root, 0);

	bool checked = true;

	init_functions_h();
	pre_load_native_functions();

	check_libraries(root);

	init_symbols_h();
	check_types(root, &checked);

	if (!checked) {
		*success = false;
		fprintf(stderr, "Type Conflict\n");
		return;
	}

	translate_to_python(root);

	destroy_functions_h();
	destroy_symbols_h();

	delete_allocated_functions();
	delete_allocated_symbols();
}