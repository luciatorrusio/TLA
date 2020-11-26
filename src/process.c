#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <tree_printing.h>
#include <process.h>
#include <project.h>
#include <translate.h>

static void check_libraries(nodeType * t);
static void check_types(nodeType * t, bool * checked);

static void check_libraries(nodeType * t){
  
}

static void check_types(nodeType * t, bool * checked){
  
}

void process_tree(nodeType * root, bool * success) {
	prefix_print(root, 0);

	bool checked = true;

	check_libraries(root);
	check_types(root, &checked);

	if (!checked) {
		*success = false;
		fprintf(stderr, "Type Conflict\n");
		return;
	}

	translate_to_python(root);
}