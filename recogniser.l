
%{
#include<stdio.h>
int rotate = 0;
int load = 0;
int num = 0;
char* arg;
enum FUNCTIONS{ROTATE, LOAD, MIRROR, COLLAGE, INVERTCOLOR};
#define FINISH 200
#define ARGUMENT 300
#define END 400
#define ERROR 800
%}
%x	ARG
%x COMMENT
WORD	[A-Za-z]
DIGIT [0-9]
%%
<INITIAL>rotate[ \t]*[(]  {BEGIN(ARG); return ROTATE; }
<INITIAL>load[ \t]*[(]   {BEGIN(ARG);return LOAD; }
<INITIAL>mirror[ \t]*[(]  {BEGIN(ARG);return MIRROR;}
<INITIAL>collage[ \t]*[(] {BEGIN(ARG);return COLLAGE;}
<INITIAL>invertColor[ \t]*[(]    {BEGIN(ARG);return INVERTCOLOR;}
<ARG>[0-9A-Za-z/\.]+	{arg = yytext; return ARGUMENT;}
<ARG>,			{num++;}
<ARG>[)] {num = 0;BEGIN(INITIAL);}
<INITIAL>;           {return END;}
<INITIAL>.	    ;
<INITIAL>\\\\   {BEGIN(COMMENT);}
<COMMENT>\n     {BEGIN(INITIAL);}
<COMMENT>.      ;
<ARG>\n      {return ERROR;}
<ARG>.	;
<INITIAL>return  {return FINISH;}
%%

int yywrap()
{
return 1;
}

int main(int argc, char **argv)
{
    if(argc > 0)
        yyin = fopen(argv[1], "r");
    else
            yyin = stdin;
    int ret = 0;
    ret = yylex();
    while(ret != FINISH && ret !=ERROR) {
        if(ret == ARGUMENT)
            printf("argument %d: %s\n", num, arg);
        if(ret == ROTATE)
            printf("rotate ");
        if(ret == LOAD)
            printf("load ");
        if(ret == MIRROR)
            printf("mirror ");
        if(ret == INVERTCOLOR)
            printf("invertcolor ");
        if(ret == COLLAGE)
            printf("collage ");
	
        ret = yylex();
    }
    if(ret == ERROR)
            printf("there has been an error ");

    return 0;
}