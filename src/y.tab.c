/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "project.y"

	#include<stdio.h>
	#include<errno.h>

	int yylex(void);
	int yyerror(const char *s);

	FILE * fp = NULL;

	int pyhead(const char * headToWrite) {
		// TODO: Write at the beggining of file
		fputs(headToWrite, fp);
	}

	int pybody(const char * bodyToWrite) {
		fputs(bodyToWrite, fp);
	}

	int success = 1;

#line 91 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   842

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

#define YYUNDEFTOK  2
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,    50,    47,     2,
      37,    38,    31,    29,    35,    30,    53,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    34,
      48,    36,    49,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,    45,    42,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    33,    33,    34,    35,    37,    38,    40,    41,    43,
      45,    46,    48,    49,    51,    52,    54,    55,    57,    58,
      60,    61,    63,    64,    65,    66,    67,    68,    70,    71,
      73,    74,    76,    77,    78,    80,    81,    83,    84,    85,
      87,    88,    90,    91,    93,    95,    96,    98,    99,   100,
     101,   102,   103,   105,   106,   107,   108,   109,   110,   112,
     113,   114,   116,   117,   119,   120,   121,   122,   124,   125,
     127,   128,   129,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   142,   143,   144,   145,   147,   148,   150,
     151,   153,   154,   156,   157,   159,   161,   162,   164,   165,
     167,   168,   170,   171,   173,   174,   176,   177,   179,   180,
     181,   182,   184,   185,   187,   188,   189,   191,   192,   193,
     194,   196,   197,   199,   200,   201,   203,   203,   203,   203,
     203,   203,   205,   206,   207,   208,   209,   210,   212,   213,
     214,   215,   217,   218,   220,   221
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "int_const", "float_const", "id",
  "string", "type_const", "DEFINE", "IF", "FOR", "DO", "WHILE", "BREAK",
  "SWITCH", "CONTINUE", "RETURN", "CASE", "DEFAULT", "PUNC", "or_const",
  "and_const", "eq_const", "shift_const", "rel_const", "inc_const",
  "param_const", "ELSE", "HEADER", "'+'", "'-'", "'*'", "'/'", "THEN",
  "';'", "','", "'='", "'('", "')'", "'['", "']'", "'{'", "'}'", "':'",
  "'?'", "'|'", "'^'", "'&'", "'<'", "'>'", "'%'", "'~'", "'!'", "'.'",
  "$accept", "program_unit", "translation_unit", "external_decl",
  "function_definition", "decl", "decl_list", "init_declarator_list",
  "init_declarator", "spec_qualifier_list", "function_declarator",
  "direct_declarator", "param_type_list", "param_list", "param_decl",
  "id_list", "initializer", "initializer_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "stat",
  "labeled_stat", "exp_stat", "compound_stat", "stat_list",
  "selection_stat", "iteration_stat", "jump_stat", "exp", "assignment_exp",
  "assignment_operator", "conditional_exp", "const_exp", "logical_or_exp",
  "logical_and_exp", "inclusive_or_exp", "exclusive_or_exp", "and_exp",
  "equality_exp", "relational_exp", "shift_expression", "additive_exp",
  "mult_exp", "cast_exp", "unary_exp", "unary_operator", "postfix_exp",
  "primary_exp", "argument_exp_list", "consts", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    43,
      45,    42,    47,   284,    59,    44,    61,    40,    41,    91,
      93,   123,   125,    58,    63,   124,    94,    38,    60,    62,
      37,   126,    33,    46
};
# endif

#define YYPACT_NINF (-118)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     117,    38,     8,   117,    65,   135,  -118,  -118,  -118,    89,
    -118,    46,  -118,   101,  -118,  -118,  -118,  -118,   761,   117,
    -118,  -118,  -118,  -118,    12,    98,  -118,   128,   466,    23,
     479,   790,  -118,  -118,  -118,    17,  -118,  -118,  -118,    47,
    -118,  -118,   -12,   164,   147,   107,   118,   187,    62,   146,
      85,    21,  -118,    30,   761,    83,  -118,  -118,     2,  -118,
     175,   182,  -118,   227,  -118,  -118,  -118,   466,  -118,  -118,
    -118,  -118,   180,    81,  -118,  -118,   179,  -118,  -118,   217,
     -10,   188,   761,  -118,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
    -118,  -118,   761,  -118,  -118,   517,   761,   220,    -1,   189,
     154,  -118,   158,  -118,     9,   184,    39,   191,   209,   427,
     210,   214,   212,   216,   546,   761,   208,  -118,  -118,  -118,
     277,  -118,  -118,  -118,  -118,   327,  -118,  -118,  -118,   113,
    -118,    41,  -118,   248,  -118,  -118,  -118,  -118,   761,  -118,
     164,    70,   147,   107,   118,   187,    62,   146,   146,   146,
      85,    21,    21,  -118,  -118,  -118,  -118,  -118,  -118,    92,
      -9,  -118,  -118,   221,   222,  -118,    18,   581,  -118,  -118,
     427,   761,   610,   242,   761,  -118,   761,  -118,  -118,   126,
     219,   427,  -118,  -118,   377,  -118,  -118,  -118,   169,  -118,
    -118,  -118,   761,   761,  -118,  -118,  -118,  -118,  -118,   225,
    -118,   215,  -118,   111,   621,   143,   228,   119,   120,  -118,
     427,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,   427,
     660,   167,   671,   761,   427,   427,  -118,   239,   427,   124,
     710,   721,   173,   132,  -118,  -118,   427,  -118,   427,   427,
     144,   427,   148,   750,   233,  -118,  -118,  -118,   427,  -118,
     427,   427,   149,  -118,  -118,  -118,  -118,   427,  -118
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     4,     5,     7,     8,    22,
      11,     0,    14,    16,   144,   145,   138,   140,     0,     0,
     139,     2,     1,     6,     0,     0,    10,     0,     0,     0,
       0,     0,   128,   129,   127,     0,   126,   130,   131,     0,
      87,    89,    93,    96,    98,   100,   102,   104,   106,   108,
     112,   114,   117,   121,     0,   123,   132,     3,    34,    21,
       0,    28,    30,     0,     9,    22,    15,     0,    17,    37,
      35,    27,     0,     0,    24,    95,     0,   121,   124,    19,
      43,     0,     0,   141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,   125,   137,     0,     0,     0,     0,     0,
      32,    33,    44,    20,     0,   138,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    67,    12,
       0,    68,    53,    54,    55,     0,    56,    57,    58,     0,
      40,     0,    25,     0,    26,    23,    18,    42,     0,    88,
      97,     0,    99,   101,   103,   105,   107,   111,   109,   110,
     113,   115,   116,   118,   119,   120,    90,   135,   142,     0,
       0,   136,    52,     0,     0,    48,     0,     0,    29,    31,
       0,     0,     0,     0,     0,    84,     0,    83,    86,     0,
       0,     0,    66,    13,     0,    65,    69,    62,     0,    38,
      36,   122,     0,     0,   134,   133,    50,    45,    51,     0,
      47,     0,    59,     0,     0,     0,     0,     0,     0,    85,
       0,    61,    64,    39,    41,    94,   143,    49,    46,     0,
       0,     0,     0,     0,     0,     0,    60,    70,     0,     0,
       0,     0,     0,     0,    73,    72,     0,    82,     0,     0,
       0,     0,     0,     0,     0,    71,    81,    80,     0,    78,
       0,     0,     0,    74,    79,    77,    76,     0,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,   104,  -118,   265,  -118,   -60,  -118,  -118,   244,   193,
    -118,   218,   -24,  -118,   159,  -118,   -63,  -118,  -118,   -29,
    -118,  -117,  -118,  -118,   250,   155,  -118,  -118,  -118,   -18,
     -27,  -118,   -21,  -115,  -118,   213,   223,   190,   211,   207,
     226,    97,   204,   108,   -39,     3,  -118,  -118,   298,  -118,
    -118
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,   130,    11,    12,    80,
      25,    13,    60,    61,    62,    73,    68,   141,    81,   111,
     112,   131,   132,   133,   134,   135,   136,   137,   138,   139,
      40,   102,    41,    76,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   169,
      20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,    69,   183,   129,   140,    72,    58,    65,    84,    75,
     190,    14,    15,    16,    17,   103,    58,    39,   196,    58,
      14,    15,    16,    17,    79,    58,    82,   108,    70,   109,
      58,   205,    85,    77,    78,   178,   108,   172,   109,   108,
      69,   109,    31,     9,    65,    18,    32,    33,    34,   100,
      59,   147,    97,    98,    35,   149,   208,    77,   163,   164,
     165,    71,   211,   212,    36,    22,   101,   151,    37,    38,
     193,    99,    10,    10,   221,   166,   198,   196,   168,   174,
      26,    27,    82,   199,   173,    83,    91,    77,   170,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,   236,    75,    82,   189,    21,   104,   201,
      92,    93,   237,   202,    95,    96,   143,   244,   245,   144,
     105,   247,   106,    57,     1,     2,    24,   203,    77,   255,
     204,   256,   257,    65,   259,   224,   107,    28,    29,    63,
      30,   264,     1,   265,   266,     3,    82,   197,    82,   229,
     268,    77,   209,    88,    82,    82,    75,   234,   235,    82,
     219,    82,   248,   213,   215,    89,   217,    82,   218,    94,
     254,    69,    14,    15,    16,    17,   226,   232,    82,    82,
      77,   225,   258,    82,    82,    86,   260,   267,   157,   158,
     159,    29,    87,    30,    31,   176,   231,   177,    32,    33,
      34,   240,    82,   161,   162,    77,    35,   253,    82,    90,
      67,   223,   239,   113,   242,   243,    36,   114,   142,   145,
      37,    38,   250,   252,    79,   171,   148,   180,   181,   175,
      14,    15,   115,    17,   116,   262,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   182,   184,   185,   186,
     187,   191,    31,   200,   216,   228,    32,    33,    34,   206,
     207,   127,   220,   227,    35,   233,   246,   263,    63,   128,
      23,    66,   146,   179,    36,    64,   110,   153,    37,    38,
      14,    15,   115,    17,   116,   194,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   155,   150,   160,   154,
      19,     0,    31,     0,     0,     0,    32,    33,    34,   152,
       0,   127,     0,     0,    35,     0,   156,     0,    63,   192,
       0,     0,     0,     0,    36,     0,     0,     0,    37,    38,
      14,    15,   115,    17,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,    32,    33,    34,     0,
       0,   127,     0,     0,    35,     0,     0,     0,    63,   195,
       0,     0,     0,     0,    36,     0,     0,     0,    37,    38,
      14,    15,   115,    17,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,    32,    33,    34,     0,
       0,   127,     0,     0,    35,     0,     0,     0,    63,   222,
       0,     0,     0,     0,    36,     0,     0,     0,    37,    38,
      14,    15,   115,    17,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,    32,    33,    34,     0,
       0,   127,     0,     0,    35,     0,     0,     0,    63,    14,
      15,    16,    17,     0,    36,     0,     0,     0,    37,    38,
       0,     0,    14,    15,    16,    17,     0,     0,     0,     0,
       0,    31,     0,     0,     0,    32,    33,    34,     0,     0,
       0,     0,     0,    35,    31,     0,     0,    67,    32,    33,
      34,     0,     0,    36,     0,     0,    35,    37,    38,    74,
      14,    15,    16,    17,     0,     0,    36,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,    32,    33,    34,    14,
      15,    16,    17,     0,    35,   167,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,    37,    38,
       0,    31,     0,     0,     0,    32,    33,    34,     0,     0,
     188,     0,     0,    35,    14,    15,    16,    17,     0,     0,
       0,     0,     0,    36,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
      32,    33,    34,    14,    15,    16,    17,     0,    35,     0,
       0,   210,     0,     0,    14,    15,    16,    17,    36,     0,
       0,     0,    37,    38,     0,    31,     0,     0,     0,    32,
      33,    34,     0,     0,   214,     0,    31,    35,     0,     0,
      32,    33,    34,     0,     0,   230,     0,    36,    35,     0,
       0,    37,    38,    14,    15,    16,    17,     0,    36,     0,
       0,     0,    37,    38,    14,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,    32,
      33,    34,     0,     0,     0,     0,    31,    35,   238,     0,
      32,    33,    34,     0,     0,   241,     0,    36,    35,     0,
       0,    37,    38,    14,    15,    16,    17,     0,    36,     0,
       0,     0,    37,    38,    14,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,    32,
      33,    34,     0,     0,     0,     0,    31,    35,   249,     0,
      32,    33,    34,    14,    15,    16,    17,    36,    35,   251,
       0,    37,    38,     0,    14,    15,    16,    17,    36,     0,
       0,     0,    37,    38,     0,    31,     0,     0,     0,    32,
      33,    34,     0,     0,     0,     0,    31,    35,   261,     0,
      32,    33,    34,    14,    15,    16,    17,    36,    35,     0,
       0,    37,    38,     0,     0,     0,     0,     0,    36,     0,
       0,     0,    37,    38,     0,    31,     0,     0,     0,    32,
      33,    34,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,    37,    38
};

static const yytype_int16 yycheck[] =
{
      18,    28,   119,    63,    67,    29,     7,     5,    20,    30,
     125,     3,     4,     5,     6,    54,     7,    35,   135,     7,
       3,     4,     5,     6,     7,     7,    35,    37,     5,    39,
       7,    40,    44,    30,    31,    26,    37,    38,    39,    37,
      67,    39,    25,     5,     5,    37,    29,    30,    31,    19,
      38,    80,    31,    32,    37,    82,    38,    54,    97,    98,
      99,    38,   177,   180,    47,     0,    36,    85,    51,    52,
     130,    50,    34,    34,   191,   102,    35,   194,   105,   108,
      34,    35,    35,    42,   108,    38,    24,    84,   106,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   220,   125,    35,   124,     3,    25,   148,
      48,    49,   229,    43,    29,    30,    35,   234,   235,    38,
      37,   238,    39,    19,     7,     8,    37,    35,   125,   246,
      38,   248,   249,     5,   251,   198,    53,    36,    37,    41,
      39,   258,     7,   260,   261,    28,    35,    34,    35,    38,
     267,   148,   176,    46,    35,    35,   177,    38,    38,    35,
      34,    35,    38,   181,   182,    47,   184,    35,   186,    23,
      38,   198,     3,     4,     5,     6,   203,    34,    35,    35,
     177,   202,    38,    35,    35,    21,    38,    38,    91,    92,
      93,    37,    45,    39,    25,    37,   214,    39,    29,    30,
      31,    34,    35,    95,    96,   202,    37,    34,    35,    22,
      41,    42,   230,    38,   232,   233,    47,    35,    38,    40,
      51,    52,   240,   241,     7,     5,    38,    43,    37,    40,
       3,     4,     5,     6,     7,   253,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    37,    37,    34,    37,
      34,    43,    25,     5,    12,    40,    29,    30,    31,    38,
      38,    34,    43,    38,    37,    37,    27,    34,    41,    42,
       5,    27,    79,   114,    47,    25,    58,    87,    51,    52,
       3,     4,     5,     6,     7,   130,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    89,    84,    94,    88,
       2,    -1,    25,    -1,    -1,    -1,    29,    30,    31,    86,
      -1,    34,    -1,    -1,    37,    -1,    90,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,     3,
       4,     5,     6,    -1,    47,    -1,    -1,    -1,    51,    52,
      -1,    -1,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    37,    25,    -1,    -1,    41,    29,    30,
      31,    -1,    -1,    47,    -1,    -1,    37,    51,    52,    40,
       3,     4,     5,     6,    -1,    -1,    47,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    30,    31,     3,
       4,     5,     6,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,
      -1,    25,    -1,    -1,    -1,    29,    30,    31,    -1,    -1,
      34,    -1,    -1,    37,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      29,    30,    31,     3,     4,     5,     6,    -1,    37,    -1,
      -1,    40,    -1,    -1,     3,     4,     5,     6,    47,    -1,
      -1,    -1,    51,    52,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    34,    -1,    25,    37,    -1,    -1,
      29,    30,    31,    -1,    -1,    34,    -1,    47,    37,    -1,
      -1,    51,    52,     3,     4,     5,     6,    -1,    47,    -1,
      -1,    -1,    51,    52,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    -1,    25,    37,    38,    -1,
      29,    30,    31,    -1,    -1,    34,    -1,    47,    37,    -1,
      -1,    51,    52,     3,     4,     5,     6,    -1,    47,    -1,
      -1,    -1,    51,    52,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    -1,    25,    37,    38,    -1,
      29,    30,    31,     3,     4,     5,     6,    47,    37,    38,
      -1,    51,    52,    -1,     3,     4,     5,     6,    47,    -1,
      -1,    -1,    51,    52,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    -1,    25,    37,    38,    -1,
      29,    30,    31,     3,     4,     5,     6,    47,    37,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    51,    52,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    28,    55,    56,    57,    58,    59,     5,
      34,    61,    62,    65,     3,     4,     5,     6,    37,   102,
     104,    55,     0,    57,    37,    64,    34,    35,    36,    37,
      39,    25,    29,    30,    31,    37,    47,    51,    52,    83,
      84,    86,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    55,     7,    38,
      66,    67,    68,    41,    78,     5,    62,    41,    70,    84,
       5,    38,    66,    69,    40,    86,    87,    99,    99,     7,
      63,    72,    35,    38,    20,    44,    21,    45,    46,    47,
      22,    24,    48,    49,    23,    29,    30,    31,    32,    50,
      19,    36,    85,    98,    25,    37,    39,    53,    37,    39,
      65,    73,    74,    38,    35,     5,     7,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    34,    42,    59,
      60,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      70,    71,    38,    35,    38,    40,    63,    73,    38,    84,
      89,    83,    90,    91,    92,    93,    94,    95,    95,    95,
      96,    97,    97,    98,    98,    98,    84,    38,    84,   103,
      83,     5,    38,    66,    73,    40,    37,    39,    26,    68,
      43,    37,    37,    75,    37,    34,    37,    34,    34,    83,
      87,    43,    42,    59,    79,    42,    75,    34,    35,    42,
       5,    98,    43,    35,    38,    40,    38,    38,    38,    66,
      40,    87,    75,    83,    34,    83,    12,    83,    83,    34,
      43,    75,    42,    42,    70,    86,    84,    38,    40,    38,
      34,    83,    34,    37,    38,    38,    75,    75,    38,    83,
      34,    34,    83,    83,    75,    75,    27,    75,    38,    38,
      83,    38,    83,    34,    38,    75,    75,    75,    38,    75,
      38,    38,    83,    34,    75,    75,    75,    38,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    55,    55,    56,    56,    57,    57,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    69,    69,    70,    70,    70,
      71,    71,    72,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    75,    75,    75,    75,    75,    76,
      76,    76,    77,    77,    78,    78,    78,    78,    79,    79,
      80,    80,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      94,    94,    95,    95,    96,    96,    96,    97,    97,    97,
      97,    98,    98,    99,    99,    99,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   102,   103,   103,   104,   104
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     2,     1,     1,     4,
       3,     2,     1,     2,     1,     3,     1,     3,     2,     1,
       3,     2,     1,     4,     3,     4,     4,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     3,     1,     3,     4,
       1,     3,     2,     1,     1,     3,     4,     3,     2,     4,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     1,     4,     3,     3,     2,     1,     2,
       5,     7,     5,     5,     7,     9,     8,     8,     7,     8,
       7,     7,     6,     2,     2,     3,     2,     1,     3,     1,
       3,     1,     1,     1,     5,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     3,     3,     2,     1,     1,
       1,     3,     1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 33 "project.y"
                                                                        { pybody("# Headers\n\n"); }
#line 1682 "y.tab.c"
    break;

  case 3:
#line 34 "project.y"
                                                                                              { pybody("# Defines\n\n"); }
#line 1688 "y.tab.c"
    break;

  case 4:
#line 35 "project.y"
                                                                                                                                                        { pybody("# Code\n\n"); }
#line 1694 "y.tab.c"
    break;

  case 9:
#line 43 "project.y"
                                                                                                { pybody("# Function definition\n\n"); }
#line 1700 "y.tab.c"
    break;


#line 1704 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 223 "project.y"


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

int yyerror(const char *msg)
{
	extern int yylineno;
	printf("Parsing Failed\nLine Number: %d %s\n",yylineno,msg);
	success = 0;
	return 0;
}

