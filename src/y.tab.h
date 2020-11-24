/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    float_const = 258,
    string = 259,
    type_const = 260,
    DEFINE = 261,
    IF = 262,
    FOR = 263,
    IN = 264,
    DO = 265,
    WHILE = 266,
    BREAK = 267,
    SWITCH = 268,
    CONTINUE = 269,
    RETURN = 270,
    CASE = 271,
    DEFAULT = 272,
    PUNC = 273,
    or_const = 274,
    and_const = 275,
    eq_const = 276,
    shift_const = 277,
    rel_const = 278,
    inc_const = 279,
    param_const = 280,
    ELSE = 281,
    HEADER = 282,
    THEN = 283,
    int_const = 284,
    id = 285
  };
#endif
/* Tokens.  */
#define float_const 258
#define string 259
#define type_const 260
#define DEFINE 261
#define IF 262
#define FOR 263
#define IN 264
#define DO 265
#define WHILE 266
#define BREAK 267
#define SWITCH 268
#define CONTINUE 269
#define RETURN 270
#define CASE 271
#define DEFAULT 272
#define PUNC 273
#define or_const 274
#define and_const 275
#define eq_const 276
#define shift_const 277
#define rel_const 278
#define inc_const 279
#define param_const 280
#define ELSE 281
#define HEADER 282
#define THEN 283
#define int_const 284
#define id 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "project.y"

    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */

#line 123 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
