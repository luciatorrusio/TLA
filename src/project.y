%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <stdarg.h>
	#include <string.h>
	#include <stdbool.h>
	#include "../includes/process.h"
	#include "../includes/project.h"

	/* prototypes */
	nodeType *str(stringT s);
	nodeType *opr(oper_types oper, int nops, ...);
	nodeType *ide(identifierT iden);
	nodeType *con(int value);
	nodeType *fco(stringT s);
	nodeType *typ(cTyp value, bool arr);
	nodeType *mop(mathOp op);
	void free_node(nodeType *p);
	int ex(nodeType *p);
	int yylex(void);
	
	void yyerror(char *s);
	int sym[26];                    /* symbol table */

	bool success = true;
	nodeType * root = NULL;

%}

%union {
		stringT sArr;
    int iValue;
		identifierT ident;
    nodeType *nPtr;
		cTyp cType;
		mathOp mOp;
};

%token IF FOR IN DO WHILE RETURN
%token or_const and_const
%token param_const ELSE
%left '+' '-'
%left '*' '/'
%nonassoc THEN
%nonassoc ELSE

%token <mOp> ass_eq eq_const shift_const rel_const inc_dec_const
%token <cType> type_const
%token <sArr> string float_const
%token <iValue> int_const
%token <ident> id

%type <nPtr> program program_unit translation_unit external_decl function_definition function_declarator 
%type <nPtr> stat exp exp_stat compound_stat jump_stat stat_list conditional_exp const_exp assignment_exp 
%type <nPtr> logical_or_exp logical_and_exp inclusive_or_exp exclusive_or_exp and_exp equality_exp relational_exp 
%type <nPtr> shift_exp additive_exp mult_exp unary_exp postfix_exp primary_exp argument_exp_list
%type <nPtr> decl initializer_list param_decl_list param_decl type_qualifier init_def_declarator
%type <nPtr> selection_stat iteration_stat unary_operator non_operable_exp arr_exp

%start program

%%
program				
              : program_unit											  {root = opr(PROG, 1, $1);}
							; 
program_unit	
              : translation_unit										{$$ = $1;}
							;
translation_unit			
              : external_decl 							        {$$ = $1;}						
							| translation_unit external_decl			{$$ = opr(TRANS_UNIT, 2, $1, $2);}
							;
external_decl				
              : function_definition						      {$$ = opr(EXT_DECL, 1, $1);}
							;
function_definition			
              : type_qualifier id function_declarator compound_stat 	{ $$ = opr(FUNC_DEF, 4, $1, ide($2), $3, $4); }			
							;
decl						
              : type_qualifier init_def_declarator ';'  {$$ = opr(DECL, 2, $1, $2);} 
							;
init_def_declarator				
              : id																	{$$ = opr(INIT_DEF_DECL, 2, ide($1), NULL);}
							| id '=' const_exp										{$$ = opr(INIT_DEF_DECL, 2, ide($1), $3);}
							; 
param_decl_list				
              : param_decl													{$$ = $1;}
							| param_decl_list ',' param_decl			{$$ = opr(PARAM_DECL_LIST, 2, $1, $3);}
							;
param_decl			
							: type_qualifier id										{$$ = opr(PARAM_DECL, 2, $1, ide($2));}
							;
type_qualifier     
							: type_const											    {$$ = typ($1, false);}
							| type_const '[' ']'								  {$$ = typ($1, true);}
							;
function_declarator	
							: '(' param_decl_list ')'				      {$$ = opr(FUNC_DEC, 1, $2);}
							| '(' ')'															{$$ = opr(FUNC_DEC, 0);}
							;
stat						
							: decl																{$$ = opr(DECL_STAT, 1, $1);}
							| exp_stat 											    	{$$ = opr(EXP_STAT, 1, $1);}
							| selection_stat 											{$$ = opr(SEL_STAT, 1, $1);}
							| jump_stat														{$$ = opr(JUMP_STAT, 1, $1);}
              | iteration_stat											{$$ = opr(ITER_STAT, 1, $1);}
							;
exp_stat					
							: exp ';'													    {$$ = $1;}
							;
compound_stat				
							: '{' stat_list '}'         					{$$ = opr(COMP_STAT, 1, $2);}
							| '{' '}'														  {$$ = opr(COMP_STAT, 0);}
							;
selection_stat				
							: IF '(' conditional_exp ')' compound_stat 											{$$ = opr(IF_STAT, 3, $3, $5, NULL);}
							| IF '(' conditional_exp ')' compound_stat ELSE compound_stat		{$$ = opr(IF_STAT, 3, $3, $5, $7);}
							;
jump_stat					
							: RETURN const_exp ';'											{$$ = opr(RET, 1, $2);}
							;
iteration_stat				
              : WHILE '(' conditional_exp ')' compound_stat			{$$ = opr(WHILE_STAT, 2, $3, $5);}
							| DO compound_stat WHILE '(' conditional_exp ')' ';'       			{$$ = opr(DO_WHILE_STAT, 2, $2, $5);}
							| FOR '(' assignment_exp ';' conditional_exp ';' assignment_exp ')' compound_stat  		{$$ = opr(FOR_STAT, 4, $3, $5, $7, $9);}
							| FOR '(' type_const id IN id ')' compound_stat			{$$ = opr(FOR_IN_STAT, 4, typ($3, false), ide($4), ide($6), $8);}
							;
stat_list					
							: stat     														{$$ = $1;}
							| stat_list stat  										{$$ = opr(STAT_LIST, 2, $1, $2);}
							;
exp							
							: assignment_exp											{$$ = $1;}
							;
assignment_exp				
							: const_exp														{$$ = $1;}
							| id '=' const_exp										{$$ = opr(ASS_EXP, 3, ide($1), NULL, $3);}
							| arr_exp '=' const_exp								{$$ = opr(ASS_EXP_A, 3, $1, NULL, $3);}
							| id ass_eq const_exp 								{$$ = opr(ASS_EXP, 3, ide($1), mop($2), $3);}
							| arr_exp ass_eq const_exp						{$$ = opr(ASS_EXP_A, 3, $1, mop($2), $3);}
							| id inc_dec_const  									{$$ = opr(ASS_EXP, 3, ide($1), mop($2), NULL);}
							| arr_exp inc_dec_const								{$$ = opr(ASS_EXP_A, 3, $1, mop($2), NULL);}
							;
const_exp					
							: conditional_exp                 		{$$ = opr(CONST_EXP_C, 1, $1);}
							| non_operable_exp										{$$ = opr(CONST_EXP_N, 1, $1);}
							;
conditional_exp
							: logical_or_exp											{$$ = $1;}
							;
logical_or_exp				
							: logical_and_exp             				{$$ = $1;}
							| logical_or_exp or_const logical_and_exp	{$$ = opr(LOG_OR_EXP, 3, $1, mop(LOG_OR), $3);}
							;
logical_and_exp				
							: inclusive_or_exp          					{$$ = $1;}
							| logical_and_exp and_const inclusive_or_exp	{$$ = opr(LOG_AND_EXP, 3, $1, mop(LOG_AND), $3);}
							;
inclusive_or_exp			
							: exclusive_or_exp										{$$ = $1;}
							| inclusive_or_exp '|' exclusive_or_exp	{$$ = opr(OR_EXP, 3, $1, mop(OR), $3);}
							;
exclusive_or_exp			
							: and_exp															{$$ = $1;}
							| exclusive_or_exp '^' and_exp				{$$ = opr(EXCL_OR_EXP, 3, $1, mop(EXCL_OR), $3);}
							;
and_exp						
							: equality_exp												{$$ = $1;}
							| and_exp '&' equality_exp 						{$$ = opr(AND_EXP, 3, $1, mop(AND), $3);}
							;
equality_exp				
							: relational_exp											{$$ = $1;}
							| equality_exp eq_const relational_exp	{$$=opr(EQU_EXP, 3, $1, mop($2), $3);}
							; 
relational_exp				
							: shift_exp									            {$$ = $1;}
							| relational_exp '<' shift_exp          {$$ = opr(REL_EXP, 3, $1, mop(L_THAN), $3 );}
							| relational_exp '>' shift_exp          {$$ = opr(REL_EXP, 3, $1, mop(G_THAN), $3 );}
							| relational_exp rel_const shift_exp    {$$ = opr(REL_EXP, 3, $1, mop($2) , $3);}
							;
shift_exp			
							: additive_exp													{$$ = $1;}
							| shift_exp shift_const additive_exp	{$$ = opr(SHI_EXP, 3, $1, mop($2), $3);}
							;
additive_exp				
							: mult_exp														{$$ = $1;}
							| additive_exp '+' mult_exp           {$$ = opr(ADD_EXP, 3, $1, mop(PLS), $3);}
							| additive_exp '-' mult_exp           {$$ = opr(ADD_EXP, 3, $1, mop(MNS), $3);}
							;
mult_exp					
							: unary_exp														{$$ = $1;}
							| mult_exp '*' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(AST), $3);}
							| mult_exp '/' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(DIV), $3);}
							| mult_exp '%' unary_exp							{$$ = opr(MULT_EXP, 3, $1, mop(MOD), $3);}
							;
unary_exp			
							: postfix_exp													{$$ = $1;}
							| unary_operator unary_exp						{$$ = opr(UNARY_EXP_OP, 2, $1, $2);}
							;
unary_operator				
							: '-'                                 {$$ = mop(MNS);}
							| '~'                                 {$$ = mop(TIL);}
							| '!' 				                        {$$ = mop(NEG);}
							;
postfix_exp					
							: primary_exp 		          					{$$ = $1;}			
							| arr_exp															{$$ = opr(POST_EXP, 1, $1);}
							| id '(' argument_exp_list ')'				{$$ = opr(POST_EXP, 2, ide($1), $3);} 
							|	id '(' ')'													{$$ = opr(POST_EXP, 2, ide($1), NULL);}
							;
arr_exp
							: id '[' conditional_exp ']' 					{$$ = opr(ARR_EXP, 2, ide($1), $3);}
							;
primary_exp					
							: id 																	{$$ = ide($1);}
							| int_const														{$$ = con($1);}
							| float_const													{$$ = fco($1);}
							| '(' conditional_exp ')'							{$$ = $2;}
							;
non_operable_exp
							: string 															{$$ = str($1);}
							| '[' initializer_list ']'						{$$ = opr(NON_OP, 1, $2);}
							| '[' initializer_list ',' ']'				{$$ = opr(NON_OP, 1, $2);}
							;
initializer_list			
							: const_exp									        {$$ = $1;}
							| initializer_list ',' const_exp		{$$ = opr(INIT_LIST, 2, $1, $3);}
							;
argument_exp_list			
							: const_exp														{$$ = $1;}
							| argument_exp_list ',' const_exp			{$$ = opr(ARG_EXP_LIST, 2, $1, $3);}
							;
%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *str(stringT s) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeStr;
	p->line = yylineno;
	strcpy(p->str.s, s);
	return p;
}

nodeType *con(int value) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeCon;
	p->con.value = value;
	p->line = yylineno;
	return p;
}

nodeType *fco(stringT s) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeFco;
	p->line = yylineno;
	strcpy(p->fco.s, s);
	return p;
}

nodeType *ide(identifierT iden) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeId;
	p->line = yylineno;
	strcpy(p->ide.i, iden);
	return p;
	} 

nodeType *opr(oper_types oper, int nops, ...) {
	extern int yylineno;
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
	p->line = yylineno;
	return p;
}

nodeType *typ(cTyp value, bool arr) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeTyp;
	p->typ.t = value;
	p->typ.arr = arr;
	p->line = yylineno;
	return p;
}

nodeType *mop(mathOp op) {
	extern int yylineno;
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeMop;
	p->mop.op = op;
	p->line = yylineno;
	return p;
}

void free_node(nodeType *p) {
	int i;
	if (!p) return;
	if (p->type == typeOpr) {
		for (i = 0; i < p->opr.nops; i++)
			free_node(p->opr.op[i]);
		free(p->opr.op);
	}
	free (p);
}

int main(int argc, char ** argv) {
		char * output_file_name;
		if (argc <= 1) {
			output_file_name = "out";
		}
		else {
			output_file_name = argv[1];
		}

    yyparse();

		if (!success) {
			free_node(root);
			return -1;
		}

		process_tree(root, output_file_name, &success);

		free_node(root);

    if(success)
    	fprintf(stderr, "Compiled successfully. Output file: '%s'\n", output_file_name);

    return 0;
}

void yyerror(char *msg)
{
	extern int yylineno;
	fprintf(stderr, "Parsing Failed\nLine Number: %d %s\n",yylineno,msg);
	success = false;
	free_node(root);
}

