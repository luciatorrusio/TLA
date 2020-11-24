%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <stdarg.h>
	#include "project.h"

	FILE * fp = NULL;

	/* prototypes */
	nodeType *opr(int oper, int nops, ...);
	nodeType *ide(int i);
	nodeType *con(int value);
	void freeNode(nodeType *p);
	int ex(nodeType *p);
	int yylex(void);
	
	void yyerror(char *s);
	int sym[26];                    /* symbol table */

		
	int pyhead(const char * headToWrite);
	int pybody(const char * bodyToWrite);

	int success = 1;
%}

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};

// %token int_const float_const id string type_const DEFINE
%token float_const string type_const DEFINE
%token IF FOR IN DO WHILE BREAK SWITCH CONTINUE RETURN CASE DEFAULT PUNC or_const and_const eq_const shift_const rel_const inc_const
%token param_const ELSE HEADER
%left '+' '-'
%left '*' '/'
%nonassoc THEN
%nonassoc ELSE
//%define parse.error verbose

%token <iValue> int_const
%token <sIndex> id

%type <nPtr> stat exp stat_list

%start program_unit

%%
program_unit				: HEADER program_unit           { pybody("# Headers\n\n"); }                    
							| DEFINE primary_exp program_unit     { pybody("# Defines\n\n"); }            	
							| translation_unit										{ pybody("# Code\n\n"); }
							;
translation_unit			: external_decl 									
							| translation_unit external_decl					
							;
external_decl				: function_definition
							| decl
							;
function_definition			: type_const id function_declarator compound_stat 	{ pybody("# Function definition\n\n"); }			
							;
decl						: type_const init_declarator_list ';' 				
							| type_const ';' 
							;
decl_list					: decl
							| decl_list decl
							;
init_declarator_list		: init_declarator
							| init_declarator_list ',' init_declarator
							;
init_declarator				: direct_declarator
							| direct_declarator '=' initializer
							;
spec_qualifier_list			: type_const spec_qualifier_list
							| type_const
							;
function_declarator			: '(' param_decl_list ')'
							| '(' ')'
							;
direct_declarator			: id 																				
							| direct_declarator '[' const_exp ']'							
							| direct_declarator '['	']'
							| direct_declarator '(' param_decl_list ')' 			
							| direct_declarator '(' param_list ')' 					
							| direct_declarator '('	')' 							
							;
param_decl_list				: param_decl
							| param_decl_list ',' param_decl
							;
param_decl					: type_const direct_declarator
							| type_const abstract_declarator
							| type_const
							;

param_list					: id
							| param_list ',' assignment_exp
							;
initializer					: assignment_exp
							| '{' initializer_list '}'
							| '{' initializer_list ',' '}'
							;
initializer_list			: initializer
							| initializer_list ',' initializer
							;
type_name					: spec_qualifier_list abstract_declarator
							| spec_qualifier_list
							;
abstract_declarator			: direct_abstract_declarator
							;
direct_abstract_declarator	: '(' abstract_declarator ')'
							| direct_abstract_declarator '[' const_exp ']'
							// | '[' const_exp ']'
							| direct_abstract_declarator '[' ']'
							| '[' ']'
							| direct_abstract_declarator '(' param_decl_list ')'
							| '(' param_decl_list ')'
							| direct_abstract_declarator '(' ')'
							| '(' ')'
							;
stat						: labeled_stat 									      	
							| exp_stat 											  	
							| compound_stat 									  	
							| selection_stat  									  
							| iteration_stat
							| jump_stat
							;
labeled_stat				: id ':' stat
							| CASE const_exp ':' stat
							| DEFAULT ':' stat
							;
exp_stat					: exp ';'
							| ';'
							;
compound_stat				: '{' decl_list stat_list '}'   						
							| '{' stat_list '}'										
							| '{' decl_list	'}'										
							| '{' '}'												
							;
stat_list					: stat     												
							| stat_list stat  										
							;
selection_stat				: IF '(' exp ')' stat 									%prec THEN
							| IF '(' exp ')' stat ELSE stat
							| SWITCH '(' exp ')' stat
							;
iteration_stat				: WHILE '(' exp ')' stat
							| DO stat WHILE '(' exp ')' ';'
							| FOR '(' exp ';' exp ';' exp ')' stat
							| FOR '(' id IN id ')' stat
							;
jump_stat				: CONTINUE ';'
							| BREAK ';'
							| RETURN exp ';'
							| RETURN ';'
							;
exp							: assignment_exp
							| exp ',' assignment_exp
							;
assignment_exp				: conditional_exp
							| unary_exp assignment_operator assignment_exp			
							;
assignment_operator			: PUNC
							| '='
							;
conditional_exp				: logical_or_exp
							| logical_or_exp '?' exp ':' conditional_exp
							;	
const_exp					: conditional_exp
							;
logical_or_exp				: logical_and_exp
							| logical_or_exp or_const logical_and_exp
							;
logical_and_exp				: inclusive_or_exp
							| logical_and_exp and_const inclusive_or_exp
							;
inclusive_or_exp			: exclusive_or_exp
							| inclusive_or_exp '|' exclusive_or_exp
							;
exclusive_or_exp			: and_exp
							| exclusive_or_exp '^' and_exp
							;
and_exp						: equality_exp
							| and_exp '&' equality_exp
							;
equality_exp				: relational_exp
							| equality_exp eq_const relational_exp
							;
relational_exp				: shift_expression
							| relational_exp '<' shift_expression
							| relational_exp '>' shift_expression
							| relational_exp rel_const shift_expression
							;
shift_expression			: additive_exp
							| shift_expression shift_const additive_exp
							;
additive_exp				: mult_exp
							| additive_exp '+' mult_exp
							| additive_exp '-' mult_exp
							;
mult_exp					: cast_exp
							| mult_exp '*' cast_exp
							| mult_exp '/' cast_exp
							| mult_exp '%' cast_exp
							;
cast_exp					: unary_exp
							| '(' type_name ')' cast_exp
							;
unary_exp					: postfix_exp
							| inc_const unary_exp
							| unary_operator cast_exp
							;
unary_operator				: '&' | '*' | '+' | '-' | '~' | '!' 				
							;
postfix_exp					: primary_exp 											
							| postfix_exp '[' exp ']'
							| postfix_exp '(' argument_exp_list ')'
							| postfix_exp '(' ')'
							| postfix_exp '.' id
							| postfix_exp inc_const

primary_exp					: id 													
							| consts 												
							| string 												
							| '(' exp ')'
							;
argument_exp_list			: assignment_exp
							| argument_exp_list ',' assignment_exp
							;
consts						: int_const 											
							| float_const
							;
%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int value) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeCon;
	p->con.value = value;
	return p;
}

nodeType *ide(int i) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeId;
	p->ide.i = i;
	return p;
	} 

nodeType *opr(int oper, int nops, ...) {
	va_list ap;
	nodeType *p;
	int i;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	if ((p->opr.op = malloc(nops * sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
	p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}

void freeNode(nodeType *p) {
	int i;
	if (!p) return;
	if (p->type == typeOpr) {
		for (i = 0; i < p->opr.nops; i++)
			freeNode(p->opr.op[i]);
		free(p->opr.op);
	}
	free (p);
}

int pyhead(const char * headToWrite) {
	// TODO: Write at the beggining of file
	fputs(headToWrite, fp);
}

int pybody(const char * bodyToWrite) {
	fputs(bodyToWrite, fp);
}

int main()
{
		fp = fopen("translated.py", "w");
		if (fp == NULL) {
			perror("fopen");
		}

    yyparse();
    if(success)
    	printf("Parsing Successful\n");


		if (fclose(fp) < 0) {
			perror("fclose");
		}

    return 0;
}

void yyerror(char *msg)
{
	extern int yylineno;
	printf("Parsing Failed\nLine Number: %d %s\n",yylineno,msg);
}

