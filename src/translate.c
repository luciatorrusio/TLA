#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <process.h>
#include <project.h>

#define MAX_INDENTATION_LEVEL 2048

FILE * fp = NULL;

static void pyhead(const char * fmt, ...);
static void pybody(const char * fmt, ...);
static void pybody_ind(const char * fmt, ...);
static void add_indentation();
static void del_indentation();
static void translate_argument_exp_list(nodeType * t);
static void translate_primary_exp(nodeType * t);
static void translate_postfix_exp(nodeType * t);
static void translate_unary_exp(nodeType * t);
static void translate_mult_exp(nodeType * t);
static void translate_additive_exp(nodeType * t);
static void translate_shift_exp(nodeType * t);
static void translate_relational_exp(nodeType * t);
static void translate_equality_exp(nodeType * t);
static void translate_and_exp(nodeType * t);
static void translate_exclusive_or_exp(nodeType * t);
static void translate_inclusive_or_exp(nodeType * t);
static void translate_logical_and_exp(nodeType * t);
static void translate_logical_or_exp(nodeType * t);
static void translate_conditional_exp(nodeType * t);
static void translate_non_operable_exp(nodeType * t);
static void translate_const_exp(nodeType * t);
static void translate_arr_exp(nodeType * t);
static void translate_assignment_exp(nodeType * t);
static void translate_exp(nodeType * t);
static void translate_exp_stat(nodeType * t);
static void translate_selection_stat(nodeType * t);
static void translate_jump_stat(nodeType * t);
static void translate_stat(nodeType * t);
static void translate_stat_list(nodeType * t);
static void translate_initializer_list(nodeType * t);
static void translate_init_def_declarator(nodeType * t);
static void translate_decl(nodeType * t);
static void translate_decl_list(nodeType * t);
static void translate_compound_stat(nodeType * t);
static void	translate_param_decl(nodeType * t);
static void	translate_param_decl_list(nodeType * t);
static void translate_function_declarator(nodeType * t);
static void translate_function_definition(nodeType * t);
static void translate_external_decl(nodeType * t);
static void translate_trans_unit(nodeType * t);
static void translate_program_unit(nodeType * t);
static void translate_prog(nodeType * t);

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

static void add_indentation() {
	if (indentLevel + 2 >= MAX_INDENTATION_LEVEL) {
		fprintf(stderr, "too much indentation\n");
	}
	indent[indentLevel++] = '\t';
	indent[indentLevel] = '\0';
}

static void del_indentation() {
	if (indentLevel == 0) {
		fprintf(stderr, "error, trying to undo indentation not possible\n");
	}
	indent[--indentLevel] = '\0';
}

static void translate_argument_exp_list(nodeType * t) {
	fprintf(stderr, "FOUND argument_exp_list\n");

  if(t->type == typeOpr && t->opr.oper == ARG_EXP_LIST && t->opr.nops == 2) {
		fprintf(stderr, "2 argumentos\n");
		nodeType * list = t->opr.op[0];
		nodeType * terminal = t->opr.op[1];
		translate_argument_exp_list(list);
		pybody(", ");
    translate_const_exp(terminal);
	}
	else {
		fprintf(stderr, "0 argumentos\n");
		translate_const_exp(t);
	}
}

static void translate_primary_exp(nodeType * t){
	fprintf(stderr, "FOUND primary_exp\n");
	
  switch(t->type) {
		case typeCon: 
			fprintf(stderr, "PRINTING CONSTANT\n");
			pybody("%d", t->con.value);
			break;
		case typeStr: 
			fprintf(stderr, "PRINTING STRING\n");
			pybody("%s", t->str.s);
			break;
		case typeId: 
			fprintf(stderr, "PRINTING IDENTIFIER\n");
			pybody("%s", t->ide.i);
			break;
		case typeTyp: 
			fprintf(stderr, "PRINTING TYPE\n");
			pybody("%d", t->typ.t);
			break;
		default:
			translate_conditional_exp(t);
			break;
	}  
}

static void translate_postfix_exp(nodeType * t) {
	fprintf(stderr, "FOUND postfix_exp\n");

	if (t->type == typeOpr && t->opr.oper == POST_EXP && t->opr.nops == 2) {
		nodeType * funName = t->opr.op[0];
		nodeType * params = t->opr.op[1];
		pybody("%s", funName->ide.i);
		pybody("(");
		if (params != NULL) {
			translate_argument_exp_list(params);
		}
		pybody(")");
	}
	else if (t->type == typeOpr && t->opr.oper == POST_EXP && t->opr.nops == 1) {
		translate_arr_exp(t->opr.op[0]);
	}
	else {
		translate_primary_exp(t);
	}
}

static void translate_unary_exp(nodeType * t){
	fprintf(stderr, "FOUND unary_exp\n");
	if(t->type == typeOpr && t->opr.oper == UNARY_EXP_OP && t->opr.nops == 2){
    nodeType * unaryOp = t->opr.op[0];
    nodeType * exp = t->opr.op[1];
		switch(unaryOp->mop.op){
			case AMP:
				pybody("&");
				translate_unary_exp(exp);
			break;
			case MNS:
				pybody("-");
				translate_unary_exp(exp);
			break;
			case TIL:
				pybody("~");
				translate_unary_exp(exp);
			break;
			case NEG:
				pybody("int( 0 == ");
				translate_unary_exp(exp);
				pybody(" )");
			break;
		}
  }
  else {
    translate_postfix_exp(t);
  }
	
}

static void translate_mult_exp(nodeType * t) {
	fprintf(stderr, "FOUND mult_exp\n");
	
	if(t->type == typeOpr && t->opr.oper == MULT_EXP && t->opr.nops == 3) {
		nodeType * first = t->opr.op[0];
		nodeType * mop = t->opr.op[1];
		nodeType * second = t->opr.op[2];

		pybody("( ");
		translate_mult_exp(first);
		switch (mop->mop.op)
		{
		case AST:
			pybody(" * ");
			break;
		case DIV:
			pybody(" / ");
			break;
		case MOD:
			pybody(" %% ");
			break;
		}
		translate_unary_exp(second);
		pybody(" )");
	}
	else {
		translate_unary_exp(t);
	}
}

static void translate_additive_exp(nodeType * t) {
	fprintf(stderr, "FOUND additive_exp\n");
	
	if( t->type == typeOpr && t->opr.oper == ADD_EXP && t->opr.nops == 3){
		nodeType *first = t->opr.op[0];
		nodeType *second = t->opr.op[2];
		nodeType *op = t->opr.op[1];
		pybody("( ");
		translate_mult_exp(first);
		switch(op->mop.op){
			case PLS:
				pybody(" + ");
			break;
			case MNS:
				pybody(" - ");
			break;
		}
		translate_mult_exp(second);
		pybody(" )");		
	}
	else {
		translate_mult_exp(t);
	}
}

static void translate_shift_exp(nodeType * t) {
	fprintf(stderr, "FOUND shift_exp\n");

	if( t->type == typeOpr && t->opr.oper == SHI_EXP && t->opr.nops == 3){
		nodeType *first = t->opr.op[0];
		nodeType *second = t->opr.op[2];
		nodeType *sym = t->opr.op[1];
		pybody("( ");
		translate_mult_exp(first);
		switch(sym->mop.op){
			case L_SHF:
				pybody(" << ");
			break;
			case R_SHF:
				pybody(" >> ");
			break;
		}
		pybody("int( ");
		translate_shift_exp(second);
		pybody(" )");	
		pybody(" )");	
	}
	else {
		translate_additive_exp(t);
	}
}


static void translate_relational_exp(nodeType *t){
	fprintf(stderr, "FOUND relational_exp\n");

	if( t->type == typeOpr && t->opr.oper == REL_EXP && t->opr.nops == 3) {
		nodeType *first = t->opr.op[0];
		nodeType *second = t->opr.op[2];
		nodeType *rel_const = t->opr.op[1];
		pybody("int( ");
		translate_relational_exp(first);
		switch (rel_const->mop.op)
		{
		case GE_THAN:
			pybody(" >= ");
			break;
		case LE_THAN:
			pybody(" <= ");
			break;
		case G_THAN:
			pybody(" > ");
			break;
		case L_THAN:
			pybody(" < ");
			break;
		}
		translate_relational_exp(second);
		pybody(" )");
	}
	else {
		translate_shift_exp(t);
	}
}

// FALTAN

static void translate_equality_exp(nodeType * t) {
	fprintf(stderr, "FOUND equality_exp\n");
  
	if( t->type == typeOpr && t->opr.oper == EQU_EXP && t->opr.nops == 3) {
		nodeType * first = t->opr.op[0];
		nodeType * sign = t->opr.op[1];
		nodeType * second = t->opr.op[2];
		pybody("int( ");
    	translate_equality_exp(first);
		switch(sign->mop.op){
		case EQ:
			pybody(" == ");
		break;
		case NEQ:
			pybody(" != ");
		break;
		}
    	translate_relational_exp(second);
		pybody(" )");

	}
	else {
		translate_relational_exp(t);
	}
}

static void translate_and_exp(nodeType * t) {
	fprintf(stderr, "FOUND and_exp\n");
	
	if( t->type == typeOpr && t->opr.oper == AND_EXP && t->opr.nops == 3) {
		nodeType * first = t->opr.op[0];
		nodeType * sign = t->opr.op[1];
		nodeType * second = t->opr.op[2];
		pybody("( ");
		translate_and_exp(first);
		if(sign->mop.op == AND) pybody(" & ");
		translate_equality_exp(second);		
		pybody(" )");
	}
	else {
		translate_equality_exp(t);
	}
}

static void translate_exclusive_or_exp(nodeType * t) {
	fprintf(stderr, "FOUND exclusive_or_exp\n");
  if(t->type == typeOpr && t->opr.oper == EXCL_OR_EXP && t->opr.nops == 3 ){
    nodeType * first = t->opr.op[0];
    nodeType * second = t->opr.op[2];
    nodeType * sign = t->opr.op[1];
		pybody("( ");
    translate_exclusive_or_exp(first);
    if(sign->mop.op == EXCL_OR)
      pybody(" ^ ");
    translate_and_exp(second);
		pybody(" )");
  }
  else{
	  translate_and_exp(t);
  }
}


static void translate_inclusive_or_exp(nodeType * t) {
	fprintf(stderr, "FOUND inclusive_or_exp\n");
  if(t->type == typeOpr && t->opr.oper == OR_EXP && t->opr.nops == 3 ){
    nodeType * first = t->opr.op[0];
    nodeType * second = t->opr.op[2];
    nodeType * sign = t->opr.op[1];
		pybody("( ");
    translate_inclusive_or_exp(first);
    if(sign->mop.op == OR)
      pybody(" | ");
    translate_exclusive_or_exp(second);
		pybody(" )");
  }
  else{
	  translate_exclusive_or_exp(t);
  }
}

static void translate_logical_and_exp(nodeType * t) {
	fprintf(stderr, "FOUND logical_and_exp\n");

	if(t->type == typeOpr && t->opr.oper == LOG_AND_EXP && t->opr.nops == 3 ){
    nodeType * first = t->opr.op[0];
    nodeType * second = t->opr.op[2];
    nodeType * sign = t->opr.op[1];
		pybody("int( ");
    translate_logical_and_exp(first);
    if(sign->mop.op == LOG_AND)
      pybody(" and ");
    translate_inclusive_or_exp(second);
		pybody(" )");
	}
	else {
		translate_inclusive_or_exp(t);
	}
}

static void translate_logical_or_exp(nodeType * t) {
	fprintf(stderr, "FOUND logical_or_exp\n");

	if(t->type == typeOpr && t->opr.oper == LOG_OR_EXP && t->opr.nops == 3 ){
    nodeType * first = t->opr.op[0];
    nodeType * second = t->opr.op[2];
    nodeType * sign = t->opr.op[1];
		pybody("int( ");
    translate_logical_or_exp(first);
    if(sign->mop.op == LOG_OR)
      pybody(" or ");
    translate_logical_and_exp(second);
		pybody(" )");
	}
	else {
		translate_logical_and_exp(t);
	}
}

static void translate_conditional_exp(nodeType * t) {
	fprintf(stderr, "FOUND conditional_exp\n");

	translate_logical_or_exp(t);
}

static void translate_non_operable_exp(nodeType * t) {
	fprintf(stderr, "FOUND non_operable_exp\n");

	if (t->type == typeOpr && t->opr.oper == NON_OP && t->opr.nops == 1) {
		pybody("[");
		translate_initializer_list(t->opr.op[0]);
		pybody("]");
	}
  else if(t->type == typeStr){
    pybody("%s", t->str.s);
  }
}

static void translate_const_exp(nodeType * t) {
	fprintf(stderr, "FOUND const_exp\n");

	if( t->type == typeOpr && t->opr.oper == CONST_EXP_C && t->opr.nops == 1 ) {
		translate_conditional_exp(t->opr.op[0]);
	}
	else if (t->type == typeOpr && t->opr.oper == CONST_EXP_N && t->opr.nops == 1) {
		translate_non_operable_exp(t->opr.op[0]);
	}

}

static void translate_arr_exp(nodeType * t) {
	fprintf(stderr, "FOUND arr_exp\n");

	if (t->type == typeOpr && t->opr.oper == ARR_EXP && t->opr.nops == 2) {
		nodeType * id = t->opr.op[0];
		nodeType * exp = t->opr.op[1];
		
		pybody("%s", id->ide.i);
		pybody("[");
		translate_conditional_exp(exp);
		pybody("]");
	}
}

static void translate_assignment_exp(nodeType * t) {
	fprintf(stderr, "FOUND assignment_exp\n");

	if (t->type != typeOpr || t->opr.nops != 3 || !(t->opr.oper == ASS_EXP || t->opr.oper == ASS_EXP_A)) {
		translate_const_exp(t);
	}
	else {
		nodeType * left_val = t->opr.op[0];
		nodeType * sign = t->opr.op[1];
		nodeType * right_val = t->opr.op[2];
		
		if (t->opr.oper == ASS_EXP) {
			pybody("%s", left_val->ide.i);
		}
		else {
			translate_arr_exp(left_val);
		}

		if (sign == NULL) {
			pybody(" = ");
			translate_const_exp(right_val);
		}
    else if(right_val == NULL){
      switch(sign->mop.op){
        case INC:
          pybody(" += 1");
        break;
        case DEC:
          pybody(" -= 1");
        break;
      }
    }
    else {
      switch(sign->mop.op){
        case ASS_DIV:
          pybody(" /= ");
        break;
        case ASS_ADD:
          pybody(" += ");
        break;
        case ASS_MOD:
          pybody(" %%= ");
        break;
        case ASS_R_SHIFT:
          pybody(" >>= ");
        break;
        case ASS_L_SHIFT:
          pybody(" <<= ");
        break;
        case ASS_SUB:
          pybody(" -= ");
        break;
        case ASS_MLT:
          pybody(" *= ");
        break;
      }

			translate_const_exp(right_val);
		}
	}
}

static void translate_exp(nodeType * t){
	fprintf(stderr, "FOUND exp\n");

	translate_assignment_exp(t);
}

static void translate_exp_stat(nodeType * t) {
	fprintf(stderr, "FOUND exp_stat\n");
	
	pybody_ind("");
	translate_exp(t);
}

static void translate_iteration_stat(nodeType *t){
	fprintf(stderr, "FOUND selection_stat\n");
  if(t->type == typeOpr && t->opr.oper == WHILE_STAT && t->opr.nops == 2) {
    nodeType * exp = t->opr.op[0];
		nodeType * stat = t->opr.op[1];
	
		pybody_ind("while(");
		translate_conditional_exp(exp);
		pybody("):\n");
		add_indentation();
		translate_compound_stat(stat);
		del_indentation();

  }
  else if(t->type == typeOpr && t->opr.oper == DO_WHILE_STAT && t->opr.nops == 2) {
		nodeType * stat = t->opr.op[0];
    nodeType * exp = t->opr.op[1];

    translate_compound_stat(stat);
    pybody_ind("while(");
		translate_conditional_exp(exp);
		pybody("):\n");
		add_indentation();
		translate_compound_stat(stat);
		del_indentation();

  }
  else if(t->type == typeOpr && t->opr.oper == FOR_STAT && t->opr.nops == 4) {
		nodeType * init = t->opr.op[0];
		nodeType * condExp = t->opr.op[1];
		nodeType * atLast = t->opr.op[2];
		nodeType * stat = t->opr.op[3];

		pybody_ind("");
    translate_assignment_exp(init);
		pybody("\n");
    pybody_ind("while(");
		translate_conditional_exp(condExp);
		pybody("):\n");
		add_indentation();
		translate_compound_stat(stat);
		pybody_ind("");
		translate_assignment_exp(atLast);
		pybody("\n");
		del_indentation();
  }
  else if(t->type == typeOpr && t->opr.oper == FOR_IN_STAT && t->opr.nops == 4){
		nodeType * el = t->opr.op[1];
		nodeType * arr = t->opr.op[2];
		nodeType * stat = t->opr.op[3];

		pybody_ind("for %s in %s:\n", el->ide.i, arr->ide.i);
		add_indentation();
		translate_compound_stat(stat);
		del_indentation();
  } 


}

static void translate_selection_stat(nodeType * t) {
	fprintf(stderr, "FOUND selection_stat\n");

	if(t->type == typeOpr && t->opr.oper == IF_STAT && t->opr.nops == 3) {
		nodeType * exp = t->opr.op[0]; 
		nodeType * ifStat = t->opr.op[1];
    nodeType * elseStat = t->opr.op[2];
    
		pybody_ind("if (");
		translate_exp(exp);
		pybody("):\n");
		add_indentation();
		translate_compound_stat(ifStat);
		del_indentation();

    if(elseStat != NULL){
			pybody_ind("else:\n");
      add_indentation();
      translate_compound_stat(elseStat);
			del_indentation();
    }
	}
	
}


static void translate_jump_stat(nodeType * t) {
	fprintf(stderr, "FOUND jump_stat\n");
	
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
	fprintf(stderr, "FOUND stat\n");
	
  if (t->type == typeOpr && t->opr.nops == 1) {
		nodeType * stat = t->opr.op[0];
		switch(t->opr.oper) {
			case EXP_STAT:
					translate_exp_stat(stat);
				break;
			case DECL_STAT:
					translate_decl(stat);
				break;
			case SEL_STAT:
					translate_selection_stat(stat);
				break;
			case JUMP_STAT:
					translate_jump_stat(stat);
				break;
      case ITER_STAT:
					translate_iteration_stat(stat);
				break;
		}
	}
}

static void translate_stat_list(nodeType * t){
	fprintf(stderr, "FOUND stat_list\n");
	
  if (t->opr.nops == 2){
		fprintf(stderr, "2 argumentos\n");
		nodeType * stat_list = t->opr.op[0];
		nodeType * stat = t->opr.op[1];
    translate_stat_list(stat_list);
		translate_stat(stat);
  } 
	else {
		fprintf(stderr, "0 argumentos\n");
		translate_stat(t);
	}
	pybody("\n");
}

static void translate_decl(nodeType * t){
	fprintf(stderr, "FOUND decl\n");
	
  if (t->type == typeOpr && t->opr.oper == DECL && t->opr.nops == 2) {
		nodeType * type = t->opr.op[0];
		nodeType * in = t->opr.op[1];
		pybody_ind("");
		translate_init_def_declarator(in);
	}
}

static void translate_direct_declarator(nodeType * t) {
	fprintf(stderr, "FOUND direct_declarator\n");

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
	fprintf(stderr, "FOUND initializer_list\n");

	if (t->type == typeOpr && t->opr.oper == INIT_LIST && t->opr.nops == 2){
		fprintf(stderr, "2 argumentos\n");
		nodeType * initializer_list = t->opr.op[0];
		nodeType * exp = t->opr.op[1];
    translate_initializer_list(initializer_list);
		pybody(", ");
		translate_const_exp(exp);
  } 
	else {
		fprintf(stderr, "0 argumentos\n");
		translate_const_exp(t);
	}
}

static void translate_init_def_declarator(nodeType * t){
	fprintf(stderr, "FOUND init_def_declarator\n");

	if (t->type == typeOpr && t->opr.oper == INIT_DEF_DECL && t->opr.nops == 2) {
		nodeType * id = t->opr.op[0];
		nodeType * exp = t->opr.op[1];

		if(exp != NULL){
			pybody("%s", id->ide.i);
			pybody(" = ");
			translate_const_exp(exp);
		}

	}
}

static void translate_compound_stat(nodeType * t) {
	fprintf(stderr, "FOUND compound_stat\n");

	if (t->type == typeOpr && t->opr.oper == COMP_STAT && t->opr.nops == 1) {
		nodeType * stat_list = t->opr.op[0];

		translate_stat_list(stat_list);
	}

}

static void	translate_param_decl(nodeType * t) {
	fprintf(stderr, "FOUND param_decl\n");

  if (t->type == typeOpr && t->opr.oper == PARAM_DECL && t->opr.nops == 2) {
		nodeType * id = t->opr.op[1];
		pybody("%s", id->ide.i);
	}
}

static void	translate_param_decl_list(nodeType * t) {
	fprintf(stderr, "FOUND param_decl_list\n");

  if(t->type == typeOpr && t->opr.oper == PARAM_DECL_LIST && t->opr.nops == 2) {
		fprintf(stderr, "2 argumentos\n");
    nodeType * param_decl_list = t->opr.op[0];
		nodeType * param_decl = t->opr.op[1];
    translate_param_decl_list(param_decl_list);
    pybody(",");
    translate_param_decl(param_decl);
  }
	else {
		fprintf(stderr, "0 argumentos\n");
		translate_param_decl(t);
	}
}


static void translate_function_declarator(nodeType * t) {
	fprintf(stderr, "FOUND function_declarator\n");

	if (t->type == typeOpr && t->opr.oper == FUNC_DEC) {
		pybody("(");
		if (t->opr.nops == 1) {
			translate_param_decl_list(t->opr.op[0]);
		}
		pybody("):\n");
	}
}

static void translate_function_definition(nodeType * t) {
	fprintf(stderr, "FOUND function_definition\n");
	if (t->opr.nops == 4) {
		nodeType * funName = t->opr.op[1];
		nodeType * funDeclarator = t->opr.op[2];
		nodeType * stmt = t->opr.op[3];

		pybody("def %s", funName->ide.i);
		
		translate_function_declarator(funDeclarator);

		add_indentation();
		translate_compound_stat(stmt);
		del_indentation();
	}
}

static void translate_external_decl(nodeType * t) {
	fprintf(stderr, "FOUND external_decl\n");

	if (t->type == typeOpr && t->opr.op[0]->opr.oper == FUNC_DEF) {
		translate_function_definition(t->opr.op[0]);
	}
}

static void translate_trans_unit(nodeType * t) {
	fprintf(stderr, "FOUND translation_unit\n");
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

static void translate_program_unit(nodeType * t){
	fprintf(stderr, "FOUND program_unit\n");

	if(t->type == typeOpr && t->opr.nops == 2 && t->opr.oper == PROG_HEADER) {
		nodeType * header = t->opr.op[0];		
		nodeType * prog_unit = t->opr.op[1];
		if(header->type == typeStr) {
			// #include                                                                  "   myArchivoDePython.py"
			int len = strlen(header->str.s);
			char * beg = strchr(header->str.s, '"');
			char * last = strrchr(header->str.s, '"');
			int realLen = (last - 1) - (beg + 1) + 1;
			if (realLen >= 0) {
				char inc[realLen+1];
				strncpy(inc, beg+1, realLen);
				inc[realLen] = 0;
				for(unsigned int i = 0; i <= strlen(inc); i++) {
					if(inc[i] == '/' || inc[i] == '\\') {
						inc[i] = '.';
					}
				}
				pybody("from %s import * \n", inc);
				translate_program_unit(prog_unit);
			}
		}
	}
	else {
		translate_trans_unit(t);
	}
}

 
static void translate_prog(nodeType * t) {
	fprintf(stderr, "FOUND program\n");

	translate_program_unit(t);
}

extern void translate_to_python(nodeType * t){
	fp = fopen("translated.py", "w");
	
	if (fp == NULL) {
			perror("fopen");
			return;
	}

	fprintf(stderr, "Translating to Python!\n");
	if (t->type == typeOpr && t->opr.oper == PROG) {
		translate_prog(t->opr.op[0]);
		pybody("\nmain()\n");
	}

	if (fclose(fp) < 0) {
    perror("fclose");
		return;
  }
}