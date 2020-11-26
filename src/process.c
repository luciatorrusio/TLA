#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <tree_printing.h>
#include <process.h>
#include <project.h>
#include <translate.h>
#include <hashtable.h>

static void add_fun_to_list(struct function_info * f);
static void pre_load_native_functions();
static void check_libraries(nodeType * t);

static void check_types_rec(nodeType * t, bool * checked);
static void check_types(nodeType * t, bool * checked);

// shorthand way to get the key from hashtable or defVal if not found
#define kh_get_val(kname, hash, key, defVal) ({k=kh_get(kname, hash, key);(k!=kh_end(hash)?kh_val(hash,k):defVal);})

// shorthand way to set value in hash with single line command.  Returns value
// returns 0=replaced existing item, 1=bucket empty (new key), 2-adding element previously deleted
#define kh_set(kname, hash, key, val) ({int ret; k = kh_put(kname, hash,key,&ret); kh_value(hash,k) = val; ret;})

#define key_is_present(table, key) (!(key == kh_end(table)))

#define MAX_PARAMS_NATIVE 10

struct params_basic_t {
	bool variable;
	unsigned int amount;
	// list
	typNodeType params[MAX_PARAMS_NATIVE];
};

struct function_info_basic {
  typNodeType ret;
  
//  char * id;

  struct params_t params;
};

static struct function_info_basic native_funcs_basic[] = {
	{
		imageTyp,
//		.id = "collage",
				true,
				1,
						imageTyp,
						true
	},
	{
		.ret = imageTyp,
//		.id = "gray_scale_image",
		.params = {
			{
				.variable = false,
				.amount = 1,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					}
				}
			}
		}
	},
	{
		.ret = imageTyp,
//		.id = "image_mirror",
		.params = {
			{
				.variable = false,
				.amount = 2,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					},
					{
						.t = stringTyp,
						.arr = false
					},
				}
			}
		}
	},
	{
		.ret = imageTyp,
//		.id = "invert_colors",
		.params = {
			{
				.variable = false,
				.amount = 1,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					}
				}
			}
		}
	},
	{
		.ret = imageTyp,
//		.id = "load_image",
		.params = {
			{
				.variable = false,
				.amount = 1,
				.params = {
					{
						.t = stringTyp,
						.arr = false
					}
				}
			}
		}
	},
	{
		.ret = imageTyp,
//		.id = "resize_image",
		.params = {
			{
				.variable = false,
				.amount = 2,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					},
					{
						.t = floatTyp,
						.arr = false
					},
				}
			}
		}
	},
	{
		.ret = imageTyp,
//		.id = "rotate_image",
		.params = {
			{
				.variable = false,
				.amount = 2,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					},
					{
						.t = intTyp,
						.arr = false
					},
				}
			}
		}
	},
	{
		.ret = intTyp,
//		.id = "save_image",
		.params = {
			{
				.variable = false,
				.amount = 2,
				.params = {
					{
						.t = stringTyp,
						.arr = false
					},
					{
						.t = imageTyp,
						.arr = false
					},
				}
			}
		}
	},
	{
		.ret = intTyp,
//		.id = "save_image_cmap",
		.params = {
			{
				.variable = false,
				.amount = 3,
				.params = {
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
			}
		}
	},
	{
		.ret = intTyp,
//		.id = "show_image",
		.params = {
			{
				.variable = false,
				.amount = 1,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					},
				}
			}
		}
	},
	{
		.ret = intTyp,
//		.id = "show_image_cmap",
		.params = {
			{
				.variable = false,
				.amount = 2,
				.params = {
					{
						.t = imageTyp,
						.arr = false
					},
					{
						.t = stringTyp,
						.arr = false
					},
				}
			}
		}
	},
};

// Global list of all functions info allocated
static struct function_info * allocated_functions;

KHASH_MAP_INIT_STR(functions_table, struct function_info *);

khash_t(functions_table) * functions_h;

static void add_fun_to_list(struct function_info * f) {
    struct function_info * l = allocated_functions;
    f->next = l;
    allocated_functions = f->next;
}

static void pre_load_native_functions() {
	int ret, is_missing;
	khiter_t k;
  	functions_h = kh_init(functions_table); // create a hashtable

	int cantFuncs = sizeof(native_funcs_basic)/sizeof(struct function_info_basic);

	for(int i = 0 ; i < cantFuncs ; i++) {
		k = kh_put(functions_table, functions_h, native_funcs_basic[i].id, &ret);
		
		struct function_info_basic * native = &native_funcs_basic[i];
		struct function_info * f = malloc(sizeof(struct function_info));
		memset(f, 0x0, sizeof(struct function_info));
		f->ret = native->ret;
		strcpy(f->id, native->id);
		f->params.variable = native->params.variable;
		f->params.amount = native->params.amount;
		f->params.params = malloc(f->params.amount * sizeof(typNodeType));
		for (unsigned j = 0; j < f->params.amount; j++) {
			memcpy(&f->params.params[j], &native->params.params[j], sizeof(typNodeType));
		}

        add_fun_to_list(f);

		kh_value(functions_h, k) = f;
	}

}

static void check_libraries(nodeType * t) {
  
}

// Global list of all symbols info allocated
static struct var_info * allocated_symbols;

// Current symbols used
static struct var_info * current_symbols;

// Symbols to be restored after current context finish
static struct var_info * to_restore_symbols;

KHASH_MAP_INIT_STR(symbols_table, struct var_info *);

khash_t(symbols_table) * symbols_h;

static void check_types_rec(nodeType * t, bool * checked);

static void check_types(nodeType * t, bool * checked) {
	int ret, is_missing;
	khiter_t k;
	symbols_h = kh_init(symbols_table);
	chck_types_rec(t, checked);
}

void process_tree(nodeType * root, bool * success) {
	prefix_print(root, 0);

	bool checked = true;

	pre_load_native_functions();

	check_libraries(root);
	check_types(root, &checked);

    delete_allocated_functions();
    delete_allocated_symbols();

	if (!checked) {
		*success = false;
		fprintf(stderr, "Type Conflict\n");
		return;
	}

	translate_to_python(root);
}