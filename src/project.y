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
	nodeType *typ(cTyp value, bool arr);
	void freeNode(nodeType *p);
	int ex(nodeType *p);
	int yylex(void);
	
	void yyerror(char *s);
	int sym[26];                    /* symbol table */

	bool success = true;
	nodeType * root = NULL;

%}

%union {
		stringT sArr;
    int iValue;                 /* integer value */
    identifierT ident;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
		cTyp cType;
};

// %token int_const float_const id string type_const DEFINE
%token float_const DEFINE
%token IF FOR IN DO WHILE BREAK SWITCH CONTINUE RETURN CASE DEFAULT PUNC or_const and_const eq_const shift_const rel_const inc_const
%token param_const ELSE HEADER
%left '+' '-'
%left '*' '/'
%nonassoc THEN
%nonassoc ELSE
//%define parse.error verbose

%token <cType> type_const
%token <sArr> string
%token <iValue> int_const
%token <ident> id

%type <nPtr> program program_unit translation_unit external_decl function_definition function_declarator 
%type <nPtr> stat exp exp_stat compound_stat jump_stat stat_list assignment_exp conditional_exp const_exp 
%type <nPtr> logical_or_exp logical_and_exp inclusive_or_exp exclusive_or_exp and_exp equality_exp relational_exp 
%type <nPtr> shift_expression additive_exp mult_exp cast_exp unary_exp postfix_exp primary_exp argument_exp_list
%type <nPtr> decl decl_list init_declarator direct_declarator initializer initializer_list
%type <nPtr> param_decl_list param_decl type_qualifier init_def_declarator
%type <nPtr> selection_stat iteration_stat


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
							| init_declarator ';'									{$$ = opr(DECL, 2, NULL, $1);}
							;
decl_list					
              : decl														    {$$ = $1;}
							| decl_list decl											{$$ = opr(DECL_LIST, 2, $1, $2);}
							;
init_def_declarator				
              : id																	{$$ = opr(INIT_DEF_DECL, 2, ide($1), NULL);}
							| id '=' initializer									{$$ = opr(INIT_DEF_DECL, 2, ide($1), $3);}
							;
init_declarator				
							: direct_declarator '=' initializer		{$$ = opr(INIT_DECL, 2, $1, $3);}
							;
direct_declarator						
							: id																	{$$ = opr(DIR_DECL, 2, ide($1), NULL);}
							| id '[' const_exp ']'								{$$ = opr(DIR_DECL, 2, ide($1), $3);}		
							; 
initializer					
              : assignment_exp								      {$$ = $1;}
							| '[' initializer_list ']'						{$$ = opr(INIT_LIST, 1, $2);}
							| '[' initializer_list ',' ']'				{$$ = opr(INIT_LIST, 1, $2);}
							;
initializer_list			
							: initializer									        {$$ = $1;}
							| initializer_list ',' initializer		{$$ = opr(INIT_LIST, 2, $1, $3);}
							;
param_decl_list				
              : param_decl													{$$ = $1;}
							| param_decl_list ',' param_decl			{$$ = opr(PARAM_DECL_LIST, 2, $1, $3);}
							;
param_decl			
							: type_qualifier direct_declarator		{$$ = opr(PARAM_DECL, 2, $1, $2);}
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
							: exp_stat 											    	{$$ = opr(EXP_STAT, 1, $1);}
							| compound_stat 									  	{$$ = opr(COMP_STAT, 1, $1);}
							| selection_stat 											{$$ = opr(SEL_STAT, 1, $1);}
							| jump_stat														{$$ = opr(JUMP_STAT, 1, $1);}
              | iteration_stat											{$$ = opr(ITER_STAT, 1, $1);}
							;
exp_stat					
							: exp ';'													    {$$ = $1;}
							;
compound_stat				
							: '{' decl_list stat_list '}'         {$$ = opr(COMP_STAT, 2, $2, $3);}					
							| '{' stat_list '}'									  {$$ = opr(COMP_STAT, 2, NULL, $2);}
							| '{' decl_list	'}'								  	{$$ = opr(COMP_STAT, 2, $2, NULL);}
							| '{' '}'														  {$$ = opr(COMP_STAT, 0);}
							;
selection_stat				
							: IF '(' exp ')' compound_stat 											{$$ = opr(IF_STAT, 3, $3, $5, NULL);}
							| IF '(' exp ')' compound_stat ELSE compound_stat		{$$ = opr(IF_STAT, 3, $3, $5, $7);}
							;
jump_stat					
							: RETURN exp ';'											{$$ = opr(RET, 1, $2);}
							| RETURN ';'													{$$ = opr(RET, 0);}
							;
iteration_stat				
              : WHILE '(' exp ')' compound_stat			{$$ = opr(WHILE_STAT, 2, $3, $5);}
							| DO compound_stat WHILE '(' exp ')' ';'       			{$$ = opr(DO_WHILE_STAT, 2, $2, $5);}
							| FOR '(' exp ';' exp ';' exp ')' compound_stat  		{$$ = opr(FOR_STAT, 4, $3, $5, $7, $9);}
							| FOR '(' type_const id IN id ')' compound_stat			{$$ = opr(FOR_IN_STAT, 4, $3, ide($4), ide($6), $8);}
							;
stat_list					
							: stat     														{$$ = $1;}
							| stat_list stat  										{$$ = opr(STAT_LIST, 2, $1, $2);}
							;

exp							
							: assignment_exp											{$$ = $1;}
							;
assignment_exp				
							: conditional_exp											{$$ = $1;}	
							;
conditional_exp				
							: logical_or_exp											{$$ = $1;}
							;	
const_exp					
							: conditional_exp                 		{$$ = $1;}
							;
logical_or_exp				
							: logical_and_exp             				{$$ = $1;}
							;
logical_and_exp				
							: inclusive_or_exp          					{$$ = $1;}
							;
inclusive_or_exp			
							: exclusive_or_exp										{$$ = $1;}
							;
exclusive_or_exp			
							: and_exp															{$$ = $1;}
							;
and_exp						
							: equality_exp												{$$ = $1;}
							;
equality_exp				
							: relational_exp											{$$ = $1;}
							; 
relational_exp				
							: shift_expression										{$$ = $1;}
							;
shift_expression			
							: additive_exp												{$$ = $1;}
							;
additive_exp				
							: mult_exp														{$$ = $1;}
							;
mult_exp					
							: cast_exp														{$$ = $1;}
							;
cast_exp					
							: unary_exp														{$$ = $1;}
							;
unary_exp					
							: postfix_exp													{$$ = $1;}				
							;
postfix_exp					
							: primary_exp 		          					{$$ = $1;}				
							| id '(' argument_exp_list ')'				{$$ = opr(POST_EXP, 2, ide($1), $3);} 
							|	id '(' ')'													{$$ = opr(POST_EXP, 2, ide($1), NULL);}
							;
primary_exp					
							: id 																	{$$ = ide($1);}
							| int_const														{$$ = con($1);}
							| string 															{$$ = str($1);}
							| '(' exp ')'													{$$ = $2;}
							;
argument_exp_list			
							: assignment_exp											{$$ = $1;}
							| argument_exp_list ',' assignment_exp	{$$ = opr(ARG_EXP_LIST, 2, $1, $3);}
							;
%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *str(stringT s) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeStr;
	strcpy(p->str.s, s);
	return p;
}

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

nodeType *ide(identifierT iden) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeId;
	strcpy(p->ide.i, iden);
	return p;
	} 

nodeType *opr(oper_types oper, int nops, ...) {
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

nodeType *typ(cTyp value, bool arr) {
	nodeType *p;
	/* allocate node */
	if ((p = malloc(sizeof(nodeType))) == NULL)
	yyerror("out of memory");
	/* copy information */
	p->type = typeTyp;
	p->typ.t = value;
	p->typ.arr = arr;
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

int main()
{
    yyparse();

		if (!success)
			return -1;

		processTree(root, &success);

    if(success)
    	printf("Parsing Successful\n");

    return 0;
}

void yyerror(char *msg)
{
	extern int yylineno;
	printf("Parsing Failed\nLine Number: %d %s\n",yylineno,msg);
	success = false;
}

