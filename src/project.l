%option yylineno

%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"../includes/project.h"
	#include"../target/y.tab.h"
	#include<math.h>
%}
%%
"img"																											{yylval.cType = imageTyp; return type_const;}
"string"																									{yylval.cType = stringTyp; return type_const;}
"int"																											{yylval.cType = intTyp; return type_const;}
"float"																										{yylval.cType = floatTyp; return type_const;}
"if"																											{return IF;}
"else"																										{return ELSE;}
"for"																											{return FOR;}
"in"																											{return IN;}
"do"																											{return DO;}
"while"																										{return WHILE;}
"return"																									{return RETURN;}
"||" 																											{return or_const;}
"&&"																											{return and_const;}
"=="																											{yylval.mOp = EQ; return eq_const;}
"!="																											{yylval.mOp = NEQ; return eq_const;}
"<="																											{yylval.mOp = LE_THAN; return rel_const;}
">="																											{yylval.mOp = GE_THAN; return rel_const;}
">>"																											{yylval.mOp = R_SHF; return shift_const;}
"<<"																											{yylval.mOp = L_SHF; return shift_const;}
"++"																											{yylval.mOp = INC; return inc_dec_const;}
"--"																											{yylval.mOp = DEC; return inc_dec_const;}
";"|"="|","|"{"|"}"|"("|")"|"["|"]"|"*"|"+"|"-"|"/"|"?"|":"|"&"|"|"|"^"|"!"|"~"|"%"|"<"|">"					{return yytext[0];}
"*="                                                      {yylval.mOp = ASS_MLT; return ass_eq;}
"/="                                                      {yylval.mOp = ASS_DIV; return ass_eq;}
"+="                                                      {yylval.mOp = ASS_ADD; return ass_eq;}
"%="																											{yylval.mOp = ASS_MOD; return ass_eq;}
">>="																											{yylval.mOp = ASS_R_SHIFT; return ass_eq;}
"-="																											{yylval.mOp = ASS_SUB; return ass_eq;}
"<<="																											{yylval.mOp = ASS_L_SHIFT; return ass_eq;}
[0-9]+																										{yylval.iValue = atoi(yytext); return int_const;}
[0-9]+"."[0-9]+([eE][-+]?[0-9]+)?																				{strcpy(yylval.sArr, yytext); return float_const;}	
[a-zA-Z_][a-zA-Z_0-9]*			 															{strcpy(yylval.ident, yytext); return id;}
\"(\\.|[^\"])*\"																					{strcpy(yylval.sArr, yytext); return string;}
"//"(\\.|[^\n])*[\n]																			;
[/][*]([^*]|[*]*[^*/])*[*]+[/]                            ;
[ \t\n]																										;
%%

int yywrap(void)
{
    return 1;
}
