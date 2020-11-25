#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <process.h>
#include <project.h>

#define MAX_INDENTATION_LEVEL 2048

FILE * fp = NULL;

static void pybody(const char * fmt, ...);
static void prefixPrint(nodeType * t, int depth);
static void addIndentation();
static void delIndentation();
static void printParams(nodeType * t);
static void translate_argument_exp_list(nodeType * t);
static void translate_primary_exp(nodeType * t);
static void translate_postfix_exp(nodeType * t);
static void translate_const_exp(nodeType *t);
static void translate_assignment_exp(nodeType * t);
static void translate_exp(nodeType * t);
static void translate_exp_stat(nodeType *t);
static void translate_jump_stat(nodeType *t);
static void translate_stat(nodeType *t);
static void translate_stat_list(nodeType * t);
static void translate_direct_declarator(nodeType * t);
static void translate_initializer_list(nodeType * t);
static void translate_initializer(nodeType * t);
static void translate_init_def_declarator(nodeType * t);
static void translate_init_declarator(nodeType * t);
static void translate_decl(nodeType * t);
static void translate_decl_list(nodeType * t);
static void translate_compound_stat(nodeType * t);
static void	translate_param_decl(nodeType * t);
static void	translate_param_decl_list(nodeType * t);
static void translate_function_declarator(nodeType * t);
static void translate_function_definition(nodeType * t);
static void translate_external_decl(nodeType * t);
static void translate_trans_unit(nodeType * t);
static void translate_prog(nodeType * t);
static void translateToPython(nodeType * t);
static void checkLibraries(nodeType * t);
static void checkTypes(nodeType * t, bool * checked);
static void translate_direct_declarator(nodeType * t);

char indent[MAX_INDENTATION_LEVEL];
int indentLevel = 0;

static void pyhead(const char * fmt, ...) {
	// Change pointer to beggining of file
	va_list argptr;
	va_start(argptr, fmt);
	int n = vfprintf(fp, fmt, argptr);
	va_end(argptr);
}

static void pybody(const char * fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	int n = vfprintf(fp, fmt, argptr);
	va_end(argptr);
}

static void pybody_ind(const char * fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	if (indentLevel > 0) {
		fprintf(fp, "%s", indent);
	}
	int n = vfprintf(fp, fmt, argptr);
	va_end(argptr);
}

static void prefixPrint(nodeType * t, int depth) {
	if (t == NULL) {
		return;
	}

	char prefIndent[200] = {0};

	unsigned int j;
	
	for (j = 0; j < depth; j++) {
		prefIndent[j] = '\t';
	}

	prefIndent[j] = '\0';

	printf("%snode type: %d\n", prefIndent, t->type);

	switch(t->type) {
		case typeOpr: 
			printf("%soper: %d\n", prefIndent, t->opr.oper);
			printf("%snops: %d\n", prefIndent, t->opr.nops);
			for (unsigned int i = 0; i < t->opr.nops; i++) {
				prefixPrint(t->opr.op[i], depth+1);
			}
			break;
		case typeCon: 
			printf("%sintConst: %d\n", prefIndent, t->con.value);
			break;
		case typeStr: 
			printf("%sstring: %s\n", prefIndent, t->str.s);
			break;
		case typeId: 
			printf("%sid: %s\n", prefIndent, t->ide.i);
			break;
		case typeTyp: 
			printf("%stype: %d\n", prefIndent, t->typ.t);
			break;
	}
}

static void addIndentation() {
	if (indentLevel + 2 >= MAX_INDENTATION_LEVEL) {
		printf("too much indentation\n");
	}
	indent[indentLevel++] = '\t';
	indent[indentLevel] = '\0';
}

static void delIndentation() {
	if (indentLevel == 0) {
		printf("error, trying to undo indentation not possible\n");
	}
	indent[indentLevel--] = '\0';
}

static void translate_argument_exp_list(nodeType * t) {
	printf("FOUND argument_exp_list\n");

  if(t->type == typeOpr && t->opr.oper == ARG_EXP_LIST && t->opr.nops == 2) {
		printf("2 argumentos\n");
		nodeType * list = t->opr.op[0];
		nodeType * terminal = t->opr.op[1];
		translate_argument_exp_list(list);
    translate_assignment_exp(terminal);
	}
	else {
		printf("0 argumentos\n");
		translate_assignment_exp(t);
	}
}

static void translate_primary_exp(nodeType * t){
	printf("FOUND primary_exp\n");
	
  switch(t->type) {
		case typeOpr: 
      if(t->opr.oper == POST_EXP){
        translate_postfix_exp(t->opr.op[0]);
      } 
			break;
		case typeCon: 
			printf("PRINTING CONSTANT\n");
			pybody("%d", t->con.value);
			break;
		case typeStr: 
			printf("PRINTING STRING\n");
			pybody("%s", t->str.s);
			break;
		case typeId: 
			printf("PRINTING IDENTIFIER\n");
			pybody("%s", t->ide.i);
			break;
		case typeTyp: 
			printf("PRINTING TYPE\n");
			pybody("%d", t->typ.t);
			break;
	}  
}

static void translate_postfix_exp(nodeType * t) {
	printf("FOUND postfix_exp\n");

	if (t->opr.oper == POST_EXP && t->opr.nops == 2) {
		nodeType * funName = t->opr.op[0];
		nodeType * params = t->opr.op[1];
		pybody("%s", funName->ide.i);
		pybody("(");
		if (params != NULL) {
			translate_argument_exp_list(params);
		}
		pybody(")");
	}
	else {
		translate_primary_exp(t);
	}
}

static void translate_const_exp(nodeType * t) {
	printf("FOUND const_exp\n");

	translate_postfix_exp(t);
}

static void translate_assignment_exp(nodeType * t) {
	printf("FOUND assignment_exp\n");

	translate_const_exp(t);
}

static void translate_exp(nodeType * t){
	printf("FOUND exp\n");

	// TODO: Jump all functions

	translate_assignment_exp(t);
}

static void translate_exp_stat(nodeType * t) {
	printf("FOUND exp_stat\n");
	
	pybody_ind("");
	translate_exp(t);
}

static void translate_jump_stat(nodeType * t) {
	printf("FOUND jump_stat\n");
	
  if(t->opr.oper == RET){
    pybody_ind("return ");
    if(t->opr.nops==1){   
      translate_exp(t->opr.op[0]);
    }else {
      pybody("\n");
    }
  }
	

}

static void translate_stat(nodeType * t){
	printf("FOUND stat\n");
	
  if (t->type == typeOpr && t->opr.nops == 1) {
		nodeType * stat = t->opr.op[0];
		switch(t->opr.oper) {
			case EXP_STAT:
					translate_exp_stat(stat);
				break;
			case COMP_STAT:
					translate_compound_stat(stat);
				break;
			case JUMP_STAT:
					translate_jump_stat(stat);
				break;
		}
	}
}

static void translate_stat_list(nodeType * t){
	printf("FOUND stat_list\n");
	
  if (t->opr.nops == 2){
		printf("2 argumentos\n");
		nodeType * stat_list = t->opr.op[0];
		nodeType * stat = t->opr.op[1];
    translate_stat_list(stat_list);
		translate_stat(stat);
  } 
	else {
		printf("0 argumentos\n");
		translate_stat(t);
	}
	pybody("\n");
}

static void translate_decl(nodeType * t){
	printf("FOUND decl\n");
	
  if (t->type == typeOpr && t->opr.oper == DECL && t->opr.nops == 2) {
		nodeType * type = t->opr.op[0];
		nodeType * in = t->opr.op[1];
		pybody_ind("");
		if (type == NULL) {
			translate_init_declarator(in);
		}
		else {
			translate_init_def_declarator(in);
		}
	}
}

static void translate_direct_declarator(nodeType * t) {
	printf("FOUND direct_declarator\n");

	if(t->type == typeOpr && t->opr.oper == DIR_DECL && t->opr.nops == 2) {
		nodeType * id = t->opr.op[0];
		nodeType * p = t->opr.op[1];

		pybody("%s", id->ide.i);

		if (p != NULL) {
			pybody("[");
			translate_const_exp(p);
			pybody("]");
		}
	}

}

static void translate_initializer_list(nodeType * t) {
	printf("FOUND initializer_list\n");

	if (t->opr.nops == 2){
		printf("2 argumentos\n");
		nodeType * initializer_list = t->opr.op[0];
		nodeType * initializer = t->opr.op[1];
    translate_initializer_list(initializer_list);
		pybody(", ");
		translate_initializer(initializer);
  } 
	else {
		printf("0 argumentos\n");
		translate_initializer(t);
	}
}

static void translate_initializer(nodeType * t) {
	printf("FOUND initializer\n");

	if (t->type == typeOpr && t->opr.oper == INIT_LIST && t->opr.nops == 1) {
		nodeType * list = t->opr.op[0];
		pybody("[");
		translate_initializer_list(list);
		pybody("]");
	}
	else {
		translate_assignment_exp(t);
	}
}

static void translate_init_def_declarator(nodeType * t){
	printf("FOUND init_declarator\n");

	if (t->type == typeOpr && t->opr.oper == INIT_DEF_DECL && t->opr.nops == 2) {
		nodeType * id = t->opr.op[0];
		nodeType * initializer = t->opr.op[1];

		pybody("%s", id->ide.i);
		if(initializer != NULL){
			pybody(" = ");
			translate_initializer(initializer);
		}

	}
}

static void translate_init_declarator(nodeType * t){
	printf("FOUND init_declarator\n");

	if (t->type == typeOpr && t->opr.oper == INIT_DECL && t->opr.nops == 2) {
		nodeType * directDecl = t->opr.op[0];
		nodeType * initializer = t->opr.op[1];
		
		translate_direct_declarator(directDecl);
		
		if (initializer != NULL) {
			printf("NON NULL INITIALIZER\n");
			pybody(" = ");
			translate_initializer(initializer);
		}
	}
}

static void translate_decl_list(nodeType * t){
	printf("FOUND decl_list\n");

	if(t->type == typeOpr && t->opr.oper == DECL_LIST && t->opr.nops == 2) {
		printf("2 argumentos\n");
    nodeType * decl_list = t->opr.op[0];
		nodeType * decl = t->opr.op[1];
    translate_decl_list(decl_list);
    translate_decl(decl);
  }
	else {
		printf("0 argumentos\n");
		translate_decl(t);
	}
	pybody("\n");
}

static void translate_compound_stat(nodeType * t) {
	printf("FOUND compound_stat\n");

	if (t->type == typeOpr && t->opr.oper == COMP_STAT && t->opr.nops == 2) {
		nodeType * decl_list = t->opr.op[0];
		nodeType * stat_list = t->opr.op[1]; 

		if (decl_list != NULL) {
			translate_decl_list(decl_list);
		}
		if (stat_list != NULL) {
			translate_stat_list(stat_list);
		}
	}

}

// param_decl_list				: param_decl									{$$ = $1}
// 							| param_decl_list ',' param_decl			{$$ = opr(PARAM_DECL_LIST, 2, $1, $3);}
// 							;

static void	translate_param_decl(nodeType * t) {
	printf("FOUND param_decl\n");

  if (t->type == typeOpr && t->opr.oper == PARAM_DECL && t->opr.nops == 2) {
		translate_direct_declarator(t->opr.op[1]);
	}
}

static void	translate_param_decl_list(nodeType * t) {
	printf("FOUND param_decl_list\n");

  if(t->type == typeOpr && t->opr.oper == PARAM_DECL_LIST && t->opr.nops == 2) {
		printf("2 argumentos\n");
    nodeType * param_decl_list = t->opr.op[0];
		nodeType * param_decl = t->opr.op[1];
    translate_param_decl_list(param_decl_list);
    pybody(",");
    translate_param_decl(param_decl);
  }
	else {
		printf("0 argumentos\n");
		translate_param_decl(t);
	}
}


static void translate_function_declarator(nodeType * t) {
	printf("FOUND function_declarator\n");

	if (t->type == typeOpr && t->opr.oper == FUNC_DEC) {
		pybody("(");
		if (t->opr.nops == 1) {
			translate_param_decl_list(t->opr.op[0]);
		}
		pybody("):\n");
	}
}

static void translate_function_definition(nodeType * t) {
	printf("FOUND function_definition\n");
	if (t->opr.nops == 4) {
		nodeType * funName = t->opr.op[1];
		nodeType * funDeclarator = t->opr.op[2];
		nodeType * stmt = t->opr.op[3];

		pybody("def %s", funName->ide.i);
		
		translate_function_declarator(funDeclarator);

		addIndentation();
		translate_compound_stat(stmt);
		delIndentation();
	}
}

static void translate_external_decl(nodeType * t) {
	printf("FOUND external_decl\n");

	if (t->type == typeOpr && t->opr.op[0]->opr.oper == FUNC_DEF) {
		translate_function_definition(t->opr.op[0]);
	}
}

static void translate_trans_unit(nodeType * t) {
	printf("FOUND translation_unit\n");
	if (t->type == typeOpr && t->opr.oper == TRANS_UNIT && t->opr.nops == 2) {
		nodeType * first = t->opr.op[0];
		nodeType * second = t->opr.op[1];
		translate_trans_unit(first);
		pybody("\n");
		translate_external_decl(second);
	}
	else {
		translate_external_decl(t);
	}
}

static void translate_prog(nodeType * t) {
	printf("FOUND program\n");
	// if header o define...

	// else
	translate_trans_unit(t);
}

static void translateToPython(nodeType * t){
	printf("Translating to Python!\n");
  if (t->type == typeOpr && t->opr.oper == PROG) {
			translate_prog(t->opr.op[0]);
			pybody("\nmain()\n");
	}
}


static void checkLibraries(nodeType * t){
  
}

static void checkTypes(nodeType * t, bool * checked){
  
}

void processTree(nodeType * root, bool * success) {
	
	prefixPrint(root, 0);

	bool checked = true;

	checkTypes(root, &checked);
	checkLibraries(root);

	if (!checked) {
		*success = false;
		printf("Type Conflict\n");
		return;
	}

	fp = fopen("translated.py", "w");
	
	if (fp == NULL) {
			perror("fopen");
	}

	translateToPython(root);

  if (fclose(fp) < 0) {
    perror("fclose");
  }
}