/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 3 "./syntax.y"

	
#include <stdio.h>
#include "lex.yy.c"

int yyerror(char *msg);
treeNode* root;
extern int synErrNum;
int PrintSynErr(int,char*,int);
int prevRow=0;



/* Line 268 of yacc.c  */
#line 85 "./syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     FLOAT = 259,
     INT = 260,
     SEMI = 261,
     COMMA = 262,
     ASSIGNOP = 263,
     RELOP = 264,
     PLUS = 265,
     MINUS = 266,
     AND = 267,
     OR = 268,
     STAR = 269,
     DIV = 270,
     DOT = 271,
     NOT = 272,
     TYPE = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     NEG = 285,
     LOWER_THAN_ELSE = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 17 "./syntax.y"

	struct treeNode* type_node;



/* Line 293 of yacc.c  */
#line 158 "./syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 183 "./syntax.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      27,    29,    33,    35,    37,    43,    46,    52,    58,    60,
      61,    63,    65,    70,    75,    80,    84,    87,    91,    93,
      96,   101,   104,   107,   108,   111,   114,   117,   119,   123,
     127,   133,   141,   149,   155,   158,   159,   163,   167,   171,
     173,   177,   179,   183,   187,   191,   195,   199,   203,   207,
     211,   215,   219,   222,   225,   230,   234,   239,   243,   245,
     247,   249,   253,   258,   263,   268,   272
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    35,    34,    -1,    -1,    37,
      36,     6,    -1,    37,     6,    -1,    37,    42,    45,    -1,
      37,    42,     6,    -1,     1,     6,    -1,    41,    -1,    41,
       7,    36,    -1,    18,    -1,    38,    -1,    25,    39,    23,
      48,    24,    -1,    25,    40,    -1,    25,    39,    23,     1,
      24,    -1,    25,     1,    23,    48,    24,    -1,     3,    -1,
      -1,     3,    -1,     3,    -1,    41,    21,     5,    22,    -1,
      41,    21,     1,    22,    -1,     3,    19,    43,    20,    -1,
       3,    19,    20,    -1,     1,    20,    -1,    44,     7,    43,
      -1,    44,    -1,    37,    41,    -1,    23,    48,    46,    24,
      -1,     1,    24,    -1,    47,    46,    -1,    -1,    52,     6,
      -1,     1,     6,    -1,    52,     1,    -1,    45,    -1,    26,
      52,     6,    -1,    26,    52,     1,    -1,    27,    19,    52,
      20,    47,    -1,    27,    19,    52,    20,    47,    28,    47,
      -1,    27,    19,    52,    20,     1,    28,    47,    -1,    29,
      19,    52,    20,    47,    -1,    49,    48,    -1,    -1,    37,
      50,     6,    -1,    37,     1,     6,    -1,    37,    50,     1,
      -1,    51,    -1,    51,     7,    50,    -1,    41,    -1,    41,
       8,    52,    -1,    52,     8,    52,    -1,    52,    12,    52,
      -1,    52,    13,    52,    -1,    52,     9,    52,    -1,    52,
      10,    52,    -1,    52,    11,    52,    -1,    52,    14,    52,
      -1,    52,    15,    52,    -1,    19,    52,    20,    -1,    11,
      52,    -1,    17,    52,    -1,     3,    19,    53,    20,    -1,
       3,    19,    20,    -1,    52,    21,    52,    22,    -1,    52,
      16,     3,    -1,     3,    -1,     5,    -1,     4,    -1,    19,
       1,    20,    -1,     3,    19,     1,    20,    -1,    52,    21,
       1,    22,    -1,     1,    21,    52,    22,    -1,    52,     7,
      53,    -1,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    59,    65,    68,    75,    81,    88,    92,
      97,   101,   107,   108,   110,   114,   118,   122,   127,   128,
     130,   134,   137,   140,   144,   147,   150,   155,   158,   162,
     167,   171,   176,   180,   183,   187,   191,   195,   199,   202,
     206,   208,   212,   216,   223,   224,   226,   227,   231,   236,
     237,   239,   240,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   266,   270,   274,   279,   280
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "FLOAT", "INT", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "AND", "OR", "STAR", "DIV", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "NEG", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      36,    36,    37,    37,    38,    38,    38,    38,    39,    39,
      40,    41,    41,    41,    42,    42,    42,    43,    43,    44,
      45,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    49,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     5,     5,     1,     0,
       1,     1,     4,     4,     4,     3,     2,     3,     1,     2,
       4,     2,     2,     0,     2,     2,     2,     1,     3,     3,
       5,     7,     7,     5,     2,     0,     3,     3,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     3,     4,     3,     1,     1,
       1,     3,     4,     4,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,     0,     0,     2,     0,     0,    13,     9,
       0,    20,     0,    15,     1,     3,     0,    21,     6,     0,
      10,     0,    45,     0,    26,     0,     5,     0,     0,     0,
       8,    45,     7,     0,     0,    45,     0,     0,    25,     0,
       0,    28,    21,    11,     0,     0,    31,     0,     0,    51,
       0,    49,    17,    44,    16,    14,    29,    24,     0,    23,
      22,     0,    68,    70,    69,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,    47,     0,    48,    46,     0,
      27,    35,     0,     0,     0,    62,    63,     0,     0,     0,
       0,     0,    30,    32,    36,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    50,     0,     0,
      65,    76,     0,    71,    61,    39,    38,     0,     0,    53,
      56,    57,    58,    54,    55,    59,    60,    67,     0,     0,
      74,    72,     0,    64,     0,     0,    73,    66,    75,     0,
      40,    43,     0,     0,    42,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    19,    33,     8,    12,    13,    20,
      21,    40,    41,    71,    72,    73,    34,    35,    50,    51,
      74,   112
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -66
static const yytype_int16 yypact[] =
{
      23,    22,   -66,    19,    49,   -66,    23,   121,   -66,   -66,
      16,    32,    40,   -66,   -66,   -66,    57,    82,   -66,   105,
      -2,     7,    69,    26,   -66,    75,   -66,    85,   103,    99,
     -66,    69,   -66,     6,   115,    69,   155,   160,   -66,    85,
     140,   188,   -66,   -66,   146,   174,   -66,    42,   191,    65,
     145,   204,   -66,   -66,   -66,   -66,   177,   -66,    69,   -66,
     -66,    54,   193,   -66,   -66,   144,   144,   161,   144,   195,
     206,   -66,   189,    42,   104,   -66,   144,   -66,   -66,    85,
     -66,   -66,   144,   139,   205,     0,   136,   117,   223,   120,
     144,   144,   -66,   -66,   -66,   -66,   144,   144,   144,   144,
     144,   144,   144,   144,   224,   166,   265,   -66,   178,   133,
     -66,   194,   220,   -66,   -66,   -66,   -66,   237,   251,   265,
     289,     0,     0,   281,   273,   136,   136,   -66,   154,   208,
     -66,   -66,   144,   -66,    53,    80,   -66,   -66,   -66,    68,
     200,   -66,    80,    80,   -66,   -66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   235,   -66,   215,     4,   -66,   -66,   -66,   -27,
     -66,   196,   -66,   234,   183,    39,    67,   -66,   190,   -66,
     -65,   138
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -46
static const yytype_int16 yytable[] =
{
      85,    86,    88,    89,     7,    27,    49,    48,    29,    42,
       7,   106,    56,    30,   102,   103,   104,   108,   111,    28,
      10,   105,    11,    -4,     1,   117,   118,    36,     9,    39,
      31,   119,   120,   121,   122,   123,   124,   125,   126,    22,
     129,     2,   -19,    61,     2,    62,    63,    64,     3,    14,
     -45,     3,    49,    65,   139,   -18,    62,    63,    64,    66,
      81,    67,    39,    23,    65,    31,   -33,   111,    68,    69,
      66,    70,    67,    76,    81,    82,    31,    24,    46,    68,
      69,    61,    70,    62,    63,    64,    28,     2,    42,    82,
      37,    65,    46,     2,     3,    38,   142,    66,    47,    67,
       3,    25,    53,    31,    44,    94,    68,    69,    45,    70,
      95,    26,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   115,    16,    46,    17,   105,   116,    18,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   113,    82,    52,
     109,   105,    62,    63,    64,    84,    77,    62,    63,    64,
      65,    78,   104,   131,    82,    65,    66,   105,    67,   110,
      57,    66,    87,    67,    62,    63,    64,   128,    59,    62,
      63,    64,    65,   140,   141,    82,   136,    65,    66,    54,
      67,   144,   145,    66,    55,    67,    96,    97,    98,    99,
     100,   101,   102,   103,   104,    58,    60,    75,    28,   105,
     130,   132,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    79,    83,    92,    90,   105,    96,    97,    98,    99,
     100,   101,   102,   103,   104,    91,    82,   127,   143,   105,
     137,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     133,    15,    43,   114,   105,    96,    97,    98,    99,   100,
     101,   102,   103,   104,    80,    32,    93,   134,   105,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     0,   107,
     138,   135,   105,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    97,    98,    99,   100,   105,   102,   103,   104,
      97,    98,    99,     0,   105,   102,   103,   104,     0,    98,
      99,     0,   105,   102,   103,   104,     0,     0,     0,     0,
     105
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-66))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      65,    66,    67,    68,     0,     7,    33,     1,     1,     3,
       6,    76,    39,     6,    14,    15,    16,    82,    83,    21,
       1,    21,     3,     0,     1,    90,    91,     1,     6,    25,
      23,    96,    97,    98,    99,   100,   101,   102,   103,    23,
     105,    18,    23,     1,    18,     3,     4,     5,    25,     0,
      24,    25,    79,    11,     1,    23,     3,     4,     5,    17,
       6,    19,    58,    23,    11,    23,    24,   132,    26,    27,
      17,    29,    19,     8,     6,    21,    23,    20,    24,    26,
      27,     1,    29,     3,     4,     5,    21,    18,     3,    21,
      23,    11,    24,    18,    25,    20,    28,    17,    31,    19,
      25,    19,    35,    23,     1,     1,    26,    27,     5,    29,
       6,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     1,     1,    24,     3,    21,     6,     6,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    20,    21,    24,
       1,    21,     3,     4,     5,     1,     1,     3,     4,     5,
      11,     6,    16,    20,    21,    11,    17,    21,    19,    20,
      20,    17,     1,    19,     3,     4,     5,     1,    22,     3,
       4,     5,    11,   134,   135,    21,    22,    11,    17,    24,
      19,   142,   143,    17,    24,    19,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     7,    22,     6,    21,    21,
      22,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     7,    19,    24,    19,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    21,     3,    28,    21,
      22,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      20,     6,    27,    20,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    58,    21,    73,    20,    21,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    79,
     132,    20,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,     9,    10,    11,    12,    21,    14,    15,    16,
       9,    10,    11,    -1,    21,    14,    15,    16,    -1,    10,
      11,    -1,    21,    14,    15,    16,    -1,    -1,    -1,    -1,
      21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    33,    34,    35,    37,    38,     6,
       1,     3,    39,    40,     0,    34,     1,     3,     6,    36,
      41,    42,    23,    23,    20,    19,     6,     7,    21,     1,
       6,    23,    45,    37,    48,    49,     1,    48,    20,    37,
      43,    44,     3,    36,     1,     5,    24,    48,     1,    41,
      50,    51,    24,    48,    24,    24,    41,    20,     7,    22,
      22,     1,     3,     4,     5,    11,    17,    19,    26,    27,
      29,    45,    46,    47,    52,     6,     8,     1,     6,     7,
      43,     6,    21,    19,     1,    52,    52,     1,    52,    52,
      19,    19,    24,    46,     1,     6,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    21,    52,    50,    52,     1,
      20,    52,    53,    20,    20,     1,     6,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,     3,     1,    52,
      22,    20,     7,    20,    20,    20,    22,    22,    53,     1,
      47,    47,    28,    28,    47,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 52 "./syntax.y"
    {
												(yyval.type_node)=InitNode("Program",(yyloc).first_line);
												//$1=InitNode("ExtDefList",@$.first_line);
												InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));
												root=(yyval.type_node);
												//PrintDFS(root,0);
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 59 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDefList",(yyloc).first_line);
												//$1=InitNode("ExtDef",@$.first_line);
												//$2=InitNode("ExtDefList",@$.first_line);
												InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 65 "./syntax.y"
    {
												(yyval.type_node)=InitNode("EPSILON",(yyloc).first_line);
}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 68 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDef",(yyloc).first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("ExtDefList",@$.first_line);
												//$3=InitNode("SEMI",@$.first_line);
												InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 75 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDef",(yyloc).first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("SEMI",@$.first_line);
												InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 81 "./syntax.y"
    {				
												(yyval.type_node)=InitNode("ExtDef",(yyloc).first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("FunDec",@$.first_line);
												//$3=InitNode("CompSt",@$.first_line);
												InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 88 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDef",(yyloc).first_line);
												InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 92 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 97 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDecList",(yyloc).first_line);
												InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));
}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 101 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ExtDecList",(yyloc).first_line);
												InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 107 "./syntax.y"
    {(yyval.type_node)=InitNode("Specifier",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 108 "./syntax.y"
    {(yyval.type_node)=InitNode("Specifier",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 110 "./syntax.y"
    {
												(yyval.type_node)=InitNode("StructSpecifier",(yyloc).first_line);
												InsertNode((yyval.type_node),5,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));
}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 114 "./syntax.y"
    {
												(yyval.type_node)=InitNode("StructSpecifier",(yyloc).first_line);
												InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 118 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,"}",prevRow);
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 122 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,"}",prevRow);
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 127 "./syntax.y"
    {(yyval.type_node)=InitNode("OptTag",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 128 "./syntax.y"
    {(yyval.type_node)=InitNode("EPSILON",(yyloc).first_line);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 130 "./syntax.y"
    {(yyval.type_node)=InitNode("Tag",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 134 "./syntax.y"
    {
												(yyval.type_node)=InitNode("VarDec",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 137 "./syntax.y"
    {
												(yyval.type_node)=InitNode("VarDec",(yyloc).first_line);InsertNode((yyval.type_node),4,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 140 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,"]",prevRow);
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 144 "./syntax.y"
    {
												(yyval.type_node)=InitNode("FunDec",(yyloc).first_line);InsertNode((yyval.type_node),4,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));
}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 147 "./syntax.y"
    {
												(yyval.type_node)=InitNode("FunDec",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 150 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,")",prevRow);
}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 155 "./syntax.y"
    {
												(yyval.type_node)=InitNode("VarList",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 158 "./syntax.y"
    {
												(yyval.type_node)=InitNode("VarList",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));
}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 162 "./syntax.y"
    {
												(yyval.type_node)=InitNode("ParamDec",(yyloc).first_line);InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 167 "./syntax.y"
    {
																(yyval.type_node)=InitNode("CompSt",(yyloc).first_line);
																InsertNode((yyval.type_node),4,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));
}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 171 "./syntax.y"
    {
																++synErrNum;
																prevRow=PrintSynErr((yyloc).first_line,"}",prevRow);
}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 176 "./syntax.y"
    {
																(yyval.type_node)=InitNode("StmtList",(yyloc).first_line);
																InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 180 "./syntax.y"
    {
																(yyval.type_node)=InitNode("EPSILON",(yyloc).first_line);
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 183 "./syntax.y"
    {
																(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
																InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 187 "./syntax.y"
    {
																++synErrNum;
																prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 191 "./syntax.y"
    {
																++synErrNum;
																prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 195 "./syntax.y"
    {	
																(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
																InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));
}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 199 "./syntax.y"
    {	(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
																InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 202 "./syntax.y"
    {
																++synErrNum;
																prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 206 "./syntax.y"
    { 	(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
                                                                InsertNode((yyval.type_node),5,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 208 "./syntax.y"
    {
																(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
																InsertNode((yyval.type_node),7,(yyvsp[(1) - (7)].type_node),(yyvsp[(2) - (7)].type_node),(yyvsp[(3) - (7)].type_node),(yyvsp[(4) - (7)].type_node),(yyvsp[(5) - (7)].type_node),(yyvsp[(6) - (7)].type_node),(yyvsp[(7) - (7)].type_node));
}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 212 "./syntax.y"
    {
																++synErrNum;
																prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 216 "./syntax.y"
    {	
																(yyval.type_node)=InitNode("Stmt",(yyloc).first_line);
																InsertNode((yyval.type_node),5,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 223 "./syntax.y"
    {(yyval.type_node)=InitNode("DefList",(yyloc).first_line);InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 224 "./syntax.y"
    {(yyval.type_node)=InitNode("EPSILON",(yyloc).first_line);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 226 "./syntax.y"
    {(yyval.type_node)=InitNode("Def",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 227 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 231 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,";",prevRow);
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 236 "./syntax.y"
    {(yyval.type_node)=InitNode("DecList",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 237 "./syntax.y"
    {(yyval.type_node)=InitNode("DecList",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 239 "./syntax.y"
    {(yyval.type_node)=InitNode("Dec",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 240 "./syntax.y"
    {(yyval.type_node)=InitNode("Dec",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 244 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 245 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 246 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 247 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 248 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 249 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 250 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 251 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 252 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 253 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 254 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),2,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 255 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),4,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 256 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 257 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),4,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 258 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 259 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 260 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 261 "./syntax.y"
    {(yyval.type_node)=InitNode("Exp",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 262 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,")",prevRow);
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 266 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,")",prevRow);
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 270 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,"]",prevRow);
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 274 "./syntax.y"
    {
												++synErrNum;
												prevRow=PrintSynErr((yyloc).first_line,"]",prevRow);
}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 279 "./syntax.y"
    {(yyval.type_node)=InitNode("Args",(yyloc).first_line);InsertNode((yyval.type_node),3,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 280 "./syntax.y"
    {(yyval.type_node)=InitNode("Args",(yyloc).first_line);InsertNode((yyval.type_node),1,(yyvsp[(1) - (1)].type_node));}
    break;



/* Line 1806 of yacc.c  */
#line 2267 "./syntax.tab.c"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 282 "./syntax.y"

int yyerror(char *msg){
	//printf("syntax error\n");
    return 0;
}

int PrintSynErr(int lineno, char *miss, int prevLine){
	if(lineno!=prevLine){//prevLine is for robust in case of outputing mul err msg
		printf("Error type B at Line %d: Missing \"%s\".\n",lineno,miss);
	}
	return lineno;
}

