yacc -v project.y
lex project.l
bison -dy project.y
gcc -o a.out y.tab.c lex.yy.c -lfl -lm
./a.out < inp
