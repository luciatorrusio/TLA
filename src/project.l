%option yylineno

%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"project.h"
	#include"y.tab.h"
	#include<math.h>
%}
%%
"#include"([ ]+)?((<(\\.|[^>])+>)|(\"(\\.|[^"])+\"))			{return HEADER;}
"#define"[ ]+[a-zA-z_][a-zA-z_0-9]* 											{return DEFINE;}
"void"|"string"|"int"|"float"															{return type_const;}	
"case"																										{return CASE;}	
"default"																									{return DEFAULT;}
"if"																											{return IF;}
"switch"																									{return SWITCH;}
"else"																										{return ELSE;}
"then"																										{return THEN;}
"for"																											{return FOR;}
"in"																											{return IN;}
"do"																											{return DO;}
"while"																										{return WHILE;}
"continue"																								{return CONTINUE;}
"break"																										{return BREAK;}
"return"																									{return RETURN;}
"||" 																											{return or_const;}
"&&"																											{return and_const;}
"=="|"!="																									{return eq_const;}
"<="|">="																									{return rel_const;}
">>"|"<<"																									{return shift_const;}
"++"|"--"																									{return inc_const;}
";"|"="|","|"{"|"}"|"("|")"|"["|"]"|"*"|"+"|"-"|"/"|"?"|":"|"&"|"|"|"^"|"!"|"~"|"%"|"<"|">"					{return yytext[0];}
"*="|"/="|"+="|"%="|">>="|"-="|"<<="|"^="									{return PUNC;}
[0-9]+																										{yylval.iValue = atoi(yytext); return int_const;}
[0-9]+"."[0-9]+																						{return float_const;}	
[a-zA-Z_][a-zA-Z_0-9]*			 															{return id;}
\"(\\.|[^\"])*\"																					{return string;}
"//"(\\.|[^\n])*[\n]																			;
[/][*]([^*]|[*]*[^*/])*[*]+[/]                            ;
[ \t\n]																										;
%%

int yywrap(void)
{
    return 1;
}
