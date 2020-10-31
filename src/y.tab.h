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
    int_const = 258,
    float_const = 259,
    id = 260,
    string = 261,
    type_const = 262,
    DEFINE = 263,
    IF = 264,
    FOR = 265,
    DO = 266,
    WHILE = 267,
    BREAK = 268,
    SWITCH = 269,
    CONTINUE = 270,
    RETURN = 271,
    CASE = 272,
    DEFAULT = 273,
    PUNC = 274,
    or_const = 275,
    and_const = 276,
    eq_const = 277,
    shift_const = 278,
    rel_const = 279,
    inc_const = 280,
    param_const = 281,
    ELSE = 282,
    HEADER = 283,
    THEN = 284
  };
#endif
/* Tokens.  */
#define int_const 258
#define float_const 259
#define id 260
#define string 261
#define type_const 262
#define DEFINE 263
#define IF 264
#define FOR 265
#define DO 266
#define WHILE 267
#define BREAK 268
#define SWITCH 269
#define CONTINUE 270
#define RETURN 271
#define CASE 272
#define DEFAULT 273
#define PUNC 274
#define or_const 275
#define and_const 276
#define eq_const 277
#define shift_const 278
#define rel_const 279
#define inc_const 280
#define param_const 281
#define ELSE 282
#define HEADER 283
#define THEN 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
