#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <process.h>
#include <project.h>
#include <translate.h>

#define MAX_INDENTATION_LEVEL 2048

static void prefix_print(nodeType * t, int depth);
static void check_libraries(nodeType * t);
static void check_types(nodeType * t, bool * checked);

static void prefix_print(nodeType * t, int depth) {
	if (t == NULL) {
		return;
	}

	char prefIndent[200] = {0};

	unsigned int j;
	
	for (j = 0; j < depth; j++) {
		prefIndent[j] = '\t';
	}

	prefIndent[j] = '\0';

	char * type; 

	switch(t->type) {
		case typeOpr: 
			switch(t->typ.t) {
				case imageTyp:
					type = "Image";
					break;
				case intTyp:
					type = "Integer";
					break;
				case floatTyp:
					type = "Float";
					break;
				case stringTyp:
					type = "String";
					break;
			}
			fprintf(stderr, "%sNode Type: Operator\n", prefIndent);
			fprintf(stderr, "%s- Operator: %d\n", prefIndent, t->opr.oper);
			fprintf(stderr, "%s- Number of Operators: %d\n", prefIndent, t->opr.nops);
			for (unsigned int i = 0; i < t->opr.nops; i++) {
				fprintf(stderr, "%s--> Operator Number %d\n", prefIndent, i);
				prefix_print(t->opr.op[i], depth+1);
			}
			break;
		case typeCon: 
			fprintf(stderr, "%sNode Type: Integer Constant\n", prefIndent);
			fprintf(stderr, "%s- Constant: %d\n", prefIndent, t->con.value);
			break;
		case typeStr: 
			fprintf(stderr, "%sNode Type: String\n", prefIndent);
			fprintf(stderr, "%s-String: %s\n", prefIndent, t->str.s);
			break;
		case typeId: 
			fprintf(stderr, "%sNode Type: ID\n", prefIndent);
			fprintf(stderr, "%s- ID: %s\n", prefIndent, t->ide.i);
			break;
		case typeMop:
			fprintf(stderr, "%sNode Type: Math Operator\n", prefIndent);
			switch(t->mop.op) {
				case AMP:
					type = "& (AND)";
					break;
				case PLS:
					type = "+ (SUM)";
					break;
				case AST:
					type = "* (MULT)";
					break;
				case NEG:
					type = "! (NOT)";
					break;
				case DIV:
					type = "/ (DIV)";
					break;
				case MNS:
					type = "- (MINUS)";
					break;
				case TIL:
					type = "~ (COMP)";
					break;
				case MOD:
					type = "%% (MOD)";
					break;
				case L_THAN:
					type = "< (LESS_THAN)";
					break;
				case G_THAN:
					type = "> (GREATER_THAN)";
					break;
				case LE_THAN:
					type = "<= (LESS_EQ_THAN)";
					break;
				case GE_THAN:
					type = ">= (GREATER_EQ_THAN)";
					break;
				case L_SHF:
					type = "<< (LEFT_SHIFT)";
					break;
				case R_SHF:
					type = ">> (RIGHT_SHIFT)";
					break;
				case EQ:
					type = "== (EQUAL)";
					break;
				case NEQ:
					type = "!= (NOT_EQUAL)";
					break;	
				case AND:
					type = "& (BIT_AND)";
					break;	
				case EXCL_OR:
					type = "^ (BIT_EXC_OR)";
					break;	
				case OR:
					type = "| (BIT_OR)";
					break;	
				case LOG_AND:
					type = "&& (LOGIC_AND)";
					break;	
				case LOG_OR:
					type = "|| (LOGIC_OR)";
					break;	
				case INC:
					type = "++ (INC)";
					break;	
				case DEC:
					type = "-- (DEC)";
					break;	
				case ASS_MLT:
					type = "*= (ASSIGN_MULT)";
					break;	
				case ASS_DIV:
					type = "/= (ASSIGN_DIV)";
					break;	
				case ASS_ADD:
					type = "+= (ASSIGN_ADD)";
					break;	
				case ASS_MOD:
					type = "%%= (ASSIGN_MOD)";
					break;	
				case ASS_R_SHIFT:
					type = ">>= (ASSIGN_RIGHT_SHIFT)";
					break;	
				case ASS_SUB:
					type = "-= (ASSIGN_SUBSTRACT)";
					break;	
				case ASS_L_SHIFT:
					type = "<<= (ASSIGN_LEFT_SHIFT)";
					break;
			}
			fprintf(stderr, "%s- Operator: %s\n", prefIndent, type);
			break;
		case typeTyp:
			fprintf(stderr, "%sNode Type: Type\n", prefIndent); 
			switch(t->typ.t) {
				case imageTyp:
					type = "Image";
					break;
				case intTyp:
					type = "Integer";
					break;
				case floatTyp:
					type = "Float";
					break;
				case stringTyp:
					type = "String";
					break;
			}
			fprintf(stderr, "%s- Type: %s\n", prefIndent, type);
			break;
	}
}

static void check_libraries(nodeType * t){
  
}

static void check_types(nodeType * t, bool * checked){
  
}

void process_tree(nodeType * root, bool * success) {
	prefix_print(root, 0);

	bool checked = true;

	check_types(root, &checked);
	check_libraries(root);

	if (!checked) {
		*success = false;
		fprintf(stderr, "Type Conflict\n");
		return;
	}

	translate_to_python(root);
}