/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "src/parser.y" /* yacc.c:316  */

    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    #include <cstring>
    #include <stack>
    extern Ast ast;

    int yylex();
    int yyerror(char const*);
    ArrayType* arrayType;//数组类型
    int idx;//索引
    int* arrayValue;//数组所有元素的值
    std::stack<InitValueListExpr*> stk;//存储元素
    std::stack<StmtNode*> whileStk;
    InitValueListExpr* top;
    int leftCnt = 0;//嵌套的{个数
    int InWhileStmt = 0;
    int paramNo = 0;//函数的第几个参数
    bool hasRet=true;//类型检查06：int函数无返回值
    bool IsvoidFunc=false;//类型检查05：void函数有返回值
    bool voidOp=false;//类型检查07：检查两端如果是函数的话是否为void类型
    #include <iostream>

#line 88 "src/parser.cpp" /* yacc.c:316  */



/* Copy the first part of user declarations.  */

#line 94 "src/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 26 "src/parser.y" /* yacc.c:355  */

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 130 "src/parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    INT = 263,
    VOID = 264,
    LPAREN = 265,
    RPAREN = 266,
    LBRACE = 267,
    RBRACE = 268,
    SEMICOLON = 269,
    LBRACKET = 270,
    RBRACKET = 271,
    COMMA = 272,
    ADD = 273,
    SUB = 274,
    MUL = 275,
    DIV = 276,
    MOD = 277,
    OR = 278,
    AND = 279,
    LESS = 280,
    LESSEQUAL = 281,
    GREATER = 282,
    GREATEREQUAL = 283,
    ASSIGN = 284,
    EQUAL = 285,
    NOTEQUAL = 286,
    NOT = 287,
    CONST = 288,
    RETURN = 289,
    CONTINUE = 290,
    BREAK = 291,
    FOR = 292,
    SCANF = 293,
    PRINTF = 294,
    DO = 295,
    TILDE = 296,
    SHA = 297,
    COLON = 298,
    MLEFT = 299,
    MRIGHT = 300,
    SUBONE = 301,
    ADDONE = 302,
    ASSIGNDIV = 303,
    ASSIGNSTAR = 304,
    ASSIGNMOD = 305,
    ASSIGNADD = 306,
    ASSIGNSUB = 307,
    THEN = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "src/parser.y" /* yacc.c:355  */

    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
    SymbolEntry* se;

#line 205 "src/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 222 "src/parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    69,    70,    77,    80,    81,    82,    83,
      84,    89,    94,    95,    96,    97,   103,   116,   131,   153,
     158,   158,   169,   176,   179,   185,   185,   200,   205,   210,
     213,   227,   231,   234,   237,   240,   246,   247,   277,   287,
     305,   324,   345,   346,   375,   404,   435,   436,   465,   496,
     499,   528,   557,   586,   617,   618,   647,   678,   679,   710,
     711,   742,   745,   746,   751,   754,   761,   762,   765,   768,
     774,   778,   781,   785,   788,   800,   834,   848,   847,   894,
     909,   909,   946,   949,   956,   996,  1025,  1024,  1070,  1096,
    1122,  1122,  1155,  1158,  1163,  1166,  1172,  1182,  1172,  1218,
    1219,  1221,  1225,  1231,  1240,  1267,  1270
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "IF", "ELSE", "WHILE",
  "INT", "VOID", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON",
  "LBRACKET", "RBRACKET", "COMMA", "ADD", "SUB", "MUL", "DIV", "MOD", "OR",
  "AND", "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "ASSIGN", "EQUAL",
  "NOTEQUAL", "NOT", "CONST", "RETURN", "CONTINUE", "BREAK", "FOR",
  "SCANF", "PRINTF", "DO", "TILDE", "SHA", "COLON", "MLEFT", "MRIGHT",
  "SUBONE", "ADDONE", "ASSIGNDIV", "ASSIGNSTAR", "ASSIGNMOD", "ASSIGNADD",
  "ASSIGNSUB", "THEN", "$accept", "Program", "Stmts", "Stmt", "LVal",
  "AssignStmt", "ExprStmt", "BlockStmt", "$@1", "IfStmt", "WhileStmt",
  "@2", "BreakStmt", "ContinueStmt", "ReturnStmt", "Exp", "Cond",
  "PrimaryExp", "UnaryExp", "MulExp", "AddExp", "RelExp", "EqExp",
  "LAndExp", "LOrExp", "ConstExp", "FuncRParams", "Type", "DeclStmt",
  "VarDeclStmt", "ConstDeclStmt", "VarDefList", "ConstDefList", "VarDef",
  "@3", "ConstDef", "@4", "ArrayIndices", "InitVal", "@5", "ConstInitVal",
  "@6", "InitValList", "ConstInitValList", "FuncDef", "$@7", "@8",
  "FuncFormalParams", "FuncFParams", "FuncFParam", "FuncArrayIndices", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -128

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-128)))

#define YYTABLE_NINF -97

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     145,    32,  -128,    33,    40,  -128,  -128,   182,    64,  -128,
     182,   182,   182,    10,    77,     0,    69,    93,   145,  -128,
      68,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,    98,
    -128,  -128,    99,    41,   104,  -128,  -128,  -128,  -128,    95,
     182,   110,   182,   182,  -128,   120,  -128,   145,  -128,  -128,
    -128,   132,  -128,   125,  -128,  -128,  -128,  -128,   182,  -128,
     182,   182,   182,   182,   182,    12,    71,  -128,  -128,  -128,
       4,    41,   124,   182,   131,    41,    75,    92,   121,   133,
     149,  -128,    21,    -6,    94,  -128,  -128,   147,  -128,  -128,
    -128,    99,    99,   114,    29,   152,  -128,   162,  -128,   182,
    -128,   150,   145,   182,   182,   182,   182,   182,   182,   182,
     182,  -128,  -128,   172,    50,  -128,   132,  -128,   155,  -128,
    -128,  -128,    10,    60,  -128,  -128,  -128,   163,    41,    41,
      41,    41,    75,    75,    92,   121,   145,   157,  -128,  -128,
    -128,  -128,  -128,   114,   114,   168,   161,   156,  -128,   145,
    -128,  -128,   172,   172,  -128,    35,  -128,   159,  -128,    10,
    -128,  -128,    65,  -128,  -128,   114,   167,   173,   175,  -128,
    -128,   172,  -128,  -128,   182,  -128,  -128,   177,  -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,    35,     0,     0,    64,    65,     0,    20,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
      34,     5,     6,     7,     8,     9,    10,    11,    12,     0,
      36,    42,    46,    31,     0,    13,    66,    67,    14,     0,
       0,    17,     0,     0,    34,     0,    22,     0,    39,    40,
      41,     0,    29,     0,    28,    27,     1,     4,     0,    19,
       0,     0,     0,     0,     0,    74,     0,    71,    38,    62,
       0,    61,     0,     0,     0,    49,    54,    57,    59,    32,
       0,    33,     0,     0,     0,    73,    30,     0,    43,    44,
      45,    47,    48,     0,    75,     0,    68,     0,    37,     0,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    21,     0,     0,    69,     0,    18,    86,    84,
      76,    77,   100,    74,    70,    63,    83,    23,    50,    51,
      52,    53,    55,    56,    58,    60,     0,    90,    88,    79,
      80,    72,    85,     0,     0,     0,     0,    99,   102,     0,
      26,    89,     0,     0,    92,     0,    78,   103,    97,     0,
      24,    94,     0,    81,    87,     0,     0,   104,     0,   101,
      91,     0,    93,   105,     0,    98,    95,     0,   106
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,   142,    -8,     2,  -128,  -128,    26,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,    -7,   153,  -128,     1,    66,
     -37,    36,    86,    87,  -128,   -36,  -128,   -12,  -128,  -128,
    -128,  -128,  -128,   101,  -128,    83,  -128,     7,  -127,  -128,
    -107,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,    43,
    -128
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    44,    21,    22,    23,    47,    24,
      25,   136,    26,    27,    28,    29,    74,    30,    31,    32,
      33,    76,    77,    78,    79,   138,    70,    34,    35,    36,
      37,    66,    84,    67,   144,    85,   153,    94,   120,   143,
     139,   152,   155,   162,    38,    95,   168,   146,   147,   148,
     167
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    51,    20,    71,    72,    75,    75,    53,    41,    40,
      57,    48,    49,    50,    54,    98,   154,   156,     5,     6,
      20,    99,   -96,   113,     1,     2,     3,    40,     4,     5,
       6,     7,    69,     8,   112,     9,    71,   101,   172,    10,
      11,    93,    39,    42,    73,   161,   163,    40,   164,    20,
      43,    87,   165,    12,    13,    14,    15,    16,   121,    63,
      64,    88,    89,    90,   176,    73,   128,   129,   130,   131,
      75,    75,    75,    75,    57,    40,    71,    46,   170,   140,
       1,     2,   171,    55,    20,    96,   119,     7,    97,    93,
     114,    52,   125,    56,   127,    10,    11,    58,     1,     2,
     103,   104,   105,   106,    20,     7,    68,    65,   115,    12,
     145,   116,    59,    10,    11,    71,    71,     1,     2,    60,
      61,    62,   107,   108,     7,    73,   118,    12,   150,    91,
      92,    81,    10,    11,    71,    83,   119,   119,    20,    86,
     100,   160,   102,   132,   133,   109,    12,   145,     1,     2,
       3,    20,     4,     5,     6,     7,   110,     8,   119,     9,
     111,   117,   122,    10,    11,   123,   126,   177,   142,   149,
     151,   157,   158,   159,   166,     1,     2,    12,    13,    14,
      15,    16,     7,   173,   137,     1,     2,     8,   174,    82,
      10,    11,     7,   178,   175,   134,    80,   135,   124,   141,
      10,    11,   169,     0,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12
};

static const yytype_int16 yycheck[] =
{
       7,    13,     0,    40,    40,    42,    43,    14,     1,    15,
      18,    10,    11,    12,    14,    11,   143,   144,     8,     9,
      18,    17,    10,    29,     3,     4,     5,    15,     7,     8,
       9,    10,    39,    12,    13,    14,    73,    73,   165,    18,
      19,    29,    10,    10,    15,   152,   153,    15,    13,    47,
      10,    58,    17,    32,    33,    34,    35,    36,    29,    18,
      19,    60,    61,    62,   171,    15,   103,   104,   105,   106,
     107,   108,   109,   110,    82,    15,   113,    13,    13,    29,
       3,     4,    17,    14,    82,    14,    93,    10,    17,    29,
      83,    14,    99,     0,   102,    18,    19,    29,     3,     4,
      25,    26,    27,    28,   102,    10,    11,     3,    14,    32,
     122,    17,    14,    18,    19,   152,   153,     3,     4,    20,
      21,    22,    30,    31,    10,    15,    12,    32,   136,    63,
      64,    11,    18,    19,   171,     3,   143,   144,   136,    14,
      16,   149,    11,   107,   108,    24,    32,   159,     3,     4,
       5,   149,     7,     8,     9,    10,    23,    12,   165,    14,
      11,    14,    10,    18,    19,     3,    16,   174,    13,     6,
      13,     3,    11,    17,    15,     3,     4,    32,    33,    34,
      35,    36,    10,    16,    12,     3,     4,    12,    15,    47,
      18,    19,    10,    16,   168,   109,    43,   110,    97,   116,
      18,    19,   159,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    12,    14,
      18,    19,    32,    33,    34,    35,    36,    55,    56,    57,
      58,    59,    60,    61,    63,    64,    66,    67,    68,    69,
      71,    72,    73,    74,    81,    82,    83,    84,    98,    10,
      15,    91,    10,    10,    58,    69,    13,    62,    72,    72,
      72,    81,    14,    69,    14,    14,     0,    57,    29,    14,
      20,    21,    22,    18,    19,     3,    85,    87,    11,    69,
      80,    74,    79,    15,    70,    74,    75,    76,    77,    78,
      70,    11,    56,     3,    86,    89,    14,    69,    72,    72,
      72,    73,    73,    29,    91,    99,    14,    17,    11,    17,
      16,    79,    11,    25,    26,    27,    28,    30,    31,    24,
      23,    11,    13,    29,    91,    14,    17,    14,    12,    69,
      92,    29,    10,     3,    87,    69,    16,    57,    74,    74,
      74,    74,    75,    75,    76,    77,    65,    12,    79,    94,
      29,    89,    13,    93,    88,    81,   101,   102,   103,     6,
      57,    13,    95,    90,    92,    96,    92,     3,    11,    17,
      57,    94,    97,    94,    13,    17,    15,   104,   100,   103,
      13,    17,    92,    16,    15,    61,    94,    69,    16
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    59,    60,
      62,    61,    61,    63,    63,    65,    64,    66,    67,    68,
      68,    69,    70,    71,    71,    71,    72,    72,    72,    72,
      72,    72,    73,    73,    73,    73,    74,    74,    74,    75,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    84,
      85,    85,    86,    86,    87,    87,    87,    88,    87,    89,
      90,    89,    91,    91,    92,    92,    93,    92,    94,    94,
      95,    94,    96,    96,    97,    97,    99,   100,    98,   101,
     101,   102,   102,   103,   103,   104,   104
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     2,
       0,     4,     2,     5,     7,     0,     6,     2,     2,     2,
       3,     1,     1,     3,     1,     1,     1,     4,     3,     2,
       2,     2,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     1,     1,     1,     3,     4,
       3,     1,     3,     1,     1,     2,     3,     0,     5,     3,
       0,     5,     3,     4,     1,     2,     0,     4,     1,     2,
       0,     4,     1,     3,     1,     3,     0,     0,     8,     1,
       0,     3,     1,     2,     3,     2,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
#line 64 "src/parser.y" /* yacc.c:1646  */
    {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1446 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1452 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 71 "src/parser.y" /* yacc.c:1646  */
    {
        //两个及以上的语句
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1461 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 77 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 1469 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 80 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1475 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 81 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1481 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 82 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1487 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1493 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 84 "src/parser.y" /* yacc.c:1646  */
    {
        if(!InWhileStmt)
            fprintf(stderr, "非while语句内出现break\n");
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 1503 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 89 "src/parser.y" /* yacc.c:1646  */
    {
        if(!InWhileStmt)
            fprintf(stderr, "非whie语句内出现continue\n");
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 1513 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 94 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1519 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 95 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1525 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 96 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1531 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 98 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 1539 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 103 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[0].strtype));
        //类型检查01：常变量使用前未声明
        if(se==nullptr)
        {
            fprintf(stderr, "标识符 \"%s\" 使用前未声明\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se);
        delete [](yyvsp[0].strtype);
    }
#line 1557 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 116 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        //类型检查01：常变量使用前未声明
        if(se==nullptr)
        {
            fprintf(stderr, "标识符 \"%s\" 使用前未声明\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se, (yyvsp[0].exprtype));
        delete [](yyvsp[-1].strtype);
    }
#line 1575 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 131 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1 = identifiers->lookup((yyvsp[-1].exprtype)->getSymPtr()->toStr());
        if(se1!=nullptr)
        {
            Type* temptype1=(FunctionType*)se1->getType();
            if(temptype1->isFunc())
            {
                FunctionType* temp1=(FunctionType*)temptype1;
                if(temp1->getRetType()==TypeSystem::voidType )
                {
                    fprintf(stderr,"操作符对象不能为void函数\n");
                }
            }
            
        }
    }
#line 1599 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 153 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
    }
#line 1607 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 158 "src/parser.y" /* yacc.c:1646  */
    {
        identifiers = new SymbolTable(identifiers);
    }
#line 1615 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 161 "src/parser.y" /* yacc.c:1646  */
    {
        // midrule actions https://www.gnu.org/software/bison/manual/html_node/Using-Midrule-Actions.html
        (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));

        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
#line 1628 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "src/parser.y" /* yacc.c:1646  */
    {
        //增加一个为空情况，不加报错
        (yyval.stmttype) = new CompoundStmt();
    }
#line 1637 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 176 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1645 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1653 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 185 "src/parser.y" /* yacc.c:1646  */
    {
        InWhileStmt++;
        WhileStmt *whileNode = new WhileStmt((yyvsp[-1].exprtype));
        (yyval.stmttype) = whileNode;
        whileStk.push(whileNode);
    }
#line 1664 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 191 "src/parser.y" /* yacc.c:1646  */
    {
        StmtNode *whileNode = (yyvsp[-1].stmttype); 
        ((WhileStmt*)whileNode)->setStmt((yyvsp[0].stmttype));
        (yyval.stmttype)=whileNode;
        whileStk.pop();
        InWhileStmt--;
    }
#line 1676 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 200 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new BreakStmt(whileStk.top());
    }
#line 1684 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 205 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new ContinueStmt(whileStk.top());
    }
#line 1692 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 210 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new ReturnStmt();
    }
#line 1700 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 213 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查05：void函数携带返回值
        if(IsvoidFunc)
        {
            fprintf(stderr,"void函数有返回值\n");
            //assert(IsvoidFunc!=true);
            IsvoidFunc=false;//恢复为false
        }
        hasRet=true;
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1716 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 227 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1722 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 231 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1728 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 234 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1736 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 237 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1744 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 240 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1753 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 246 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1759 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 247 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        //类型检查03：函数使用前未声明
        if(se == nullptr)
        {    
            fprintf(stderr, "函数 \"%s\"未定义\n", (char*)(yyvsp[-3].strtype));
            //assert(1==0);
        }
        //类型检查03：形参实参个数不匹配——04需要区分同名不同参数的函数——如何区分
        //一个设想——删除得到的，再加到最后？
        int realcount=0;//实参个数
        int formcount=0;//调用函数的形参个数
        Node*temp=(Node*)(yyvsp[-1].exprtype);
        while(temp)
        {
            realcount++;//实参个数
            temp=temp->getNext();
        }
        //计算形参个数
        Type* temptype=se->getType();
        std::vector<Type*> params = ((FunctionType*)temptype)->getParamsType();
        formcount=params.size();
        if(formcount!=realcount)
        {
            fprintf(stderr,"所调用函数 \"%s\" 的形参实参个数不匹配\n",(char*)(yyvsp[-3].strtype));
            //assert(1==0);
        }
        (yyval.exprtype) = new FuncCallNode(se, (yyvsp[-1].exprtype));
    }
#line 1794 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 277 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[-2].strtype));
        //类型检查03：函数使用前未声明
        if(se == nullptr)
        {    
            fprintf(stderr, "函数 \"%s\" 未定义\n", (char*)(yyvsp[-2].strtype));
        }
        (yyval.exprtype) = new FuncCallNode(se);
    }
#line 1809 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 287 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[0].exprtype)->getSymPtr();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
        }
#line 1832 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 305 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new OneOpExpr(se, OneOpExpr::SUB, (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[0].exprtype)->getSymPtr();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
    }
#line 1856 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 324 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new OneOpExpr(se, OneOpExpr::NOT, (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[0].exprtype)->getSymPtr();
        //fprintf(stderr,"test1\n");
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                //fprintf(stderr,"是函数\n");
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {               
                    fprintf(stderr,"一元操作符对象不能为void函数\n");
                }
            }
        }
    }
#line 1880 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 345 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1886 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 346 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
#line 1920 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 375 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
#line 1954 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 404 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
#line 1988 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 435 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1994 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 436 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2028 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 465 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2062 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 496 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2070 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 499 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2104 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 528 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2138 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 557 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2172 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 586 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEREQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2206 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 617 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2212 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 618 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2246 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 647 "src/parser.y" /* yacc.c:1646  */
    {
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NOTEQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 2280 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 678 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2286 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 679 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
#line 2320 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 710 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2326 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 711 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        //类型检查07：检查两端如果是函数的话是否为void类型
        SymbolEntry* se1;
        se1=(yyvsp[-2].exprtype)->getSymPtr();
        SymbolEntry* se2;
        se2=(yyvsp[0].exprtype)->getSymPtr();
        if(se1!=nullptr)
        {
            if(((se1->getType()))->isFunc())
            {
                if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }  
        }
        if(se2!=nullptr)
        {
            if(((se2->getType()))->isFunc())
            {
                if(((FunctionType*)(se2->getType()))->getRetType()->isVoid())
                {
                    fprintf(stderr,"操作符两端不能为void函数\n");
                }
            }
        }
    }
#line 2360 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 742 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2366 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 745 "src/parser.y" /* yacc.c:1646  */
    {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2372 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 746 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        (yyval.exprtype)->setNext((yyvsp[0].exprtype));
    }
#line 2381 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 751 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.type) = TypeSystem::intType;
    }
#line 2389 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 754 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.type) = TypeSystem::voidType;
        //void只会出现在函数定义中，所以此处无问题
        IsvoidFunc=true;
    }
#line 2399 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 761 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2405 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 762 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2411 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 765 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[-1].stmttype);}
#line 2417 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 768 "src/parser.y" /* yacc.c:1646  */
    {
        // 这里肯定还得区分一下 
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 2426 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 774 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2435 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 778 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2441 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 781 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2450 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 785 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2456 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 788 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, (yyvsp[0].strtype), identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[0].strtype), se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[0].strtype));
            //assert(1==0);//中断运行
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 2473 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 801 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = (yyvsp[0].exprtype);
        while(temp)
        {
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type *type = TypeSystem::intType;
        Type* temp1;
        while(!vec.empty())
        {
            temp1 = new ArrayType(type, vec.back());
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
            vec.pop_back();
        }
        arrayType = (ArrayType*)type;
        se = new IdentifierSymbolEntry(type, (yyvsp[-1].strtype), identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setAllZero();
        int *p = new int[type->getSize()];
        ((IdentifierSymbolEntry*)se)->setArrayValue(p);
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[-1].strtype), se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[-1].strtype));
            assert(1==0);//中断运行
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 2511 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 834 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, (yyvsp[-2].strtype), identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[-2].strtype), se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[-2].strtype));
            assert(1==0);//中断运行
        }
        ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getValue());
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 2529 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 848 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        std::vector<int> vec;//记录数组各个维度长度，如a[3][2]记录3，2
        ExprNode* temp = (yyvsp[-1].exprtype);
        while(temp)
        {
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type* type = TypeSystem::intType;
        Type* temp1;
        //从最低维度开始向上计算分配的长度
        for(auto it = vec.rbegin(); it != vec.rend(); it++) 
        {
            //type.h83
            temp1 = new ArrayType(type, *it);
            //向上遍历分配
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
        }
        //arrayType此时是最高维度数组
        arrayType = (ArrayType*)type;
        idx = 0;
        //清空栈
        std::stack<InitValueListExpr*>().swap(stk);
        se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[-2].strtype), se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[-2].strtype));
            //assert(1==0);//中断运行
        }
        (yyval.se) = se;
        //为arrayvalue分配空间以记录元素
        arrayValue = new int[arrayType->getSize()];
    }
#line 2571 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 885 "src/parser.y" /* yacc.c:1646  */
    {
        ((IdentifierSymbolEntry*)(yyvsp[-1].se))->setArrayValue(arrayValue);
        if(((InitValueListExpr*)(yyvsp[0].exprtype))->isEmpty())
            ((IdentifierSymbolEntry*)(yyvsp[-1].se))->setAllZero();
        (yyval.stmttype) = new DeclStmt(new Id((yyvsp[-1].se)), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2583 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 894 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::constIntType, (yyvsp[-2].strtype), identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setConst();
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[-2].strtype), se))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[-2].strtype));
            assert(1==0);//中断运行
        }
        identifiers->install((yyvsp[-2].strtype), se);
        ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getValue());
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 2603 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 909 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = (yyvsp[-1].exprtype);
        while(temp){
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type* type = TypeSystem::constIntType;
        Type* temp1;
        for(auto it = vec.rbegin(); it != vec.rend(); it++) {
            temp1 = new ArrayType(type, *it, true);
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
        }
        arrayType = (ArrayType*)type;
        idx = 0;
        std::stack<InitValueListExpr*>().swap(stk);
        se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setConst();
        (yyval.se) = se;
        arrayValue = new int[arrayType->getSize()];
    }
#line 2632 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 933 "src/parser.y" /* yacc.c:1646  */
    {
        ((IdentifierSymbolEntry*)(yyvsp[-1].se))->setArrayValue(arrayValue);
        //类型检查02：常变量重定义
        if(!identifiers->install((yyvsp[-4].strtype), (yyvsp[-1].se)))
        {    
            fprintf(stderr, "常变量名 \"%s\" 重定义\n", (char*)(yyvsp[-4].strtype));
            assert(1==0);//中断运行
        }
        (yyval.stmttype) = new DeclStmt(new Id((yyvsp[-1].se)), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2648 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 946 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 2656 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 949 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-3].exprtype);
        (yyvsp[-3].exprtype)->setNext((yyvsp[-1].exprtype));
    }
#line 2665 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 957 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        if(!stk.empty())
        {
            //赋值
            arrayValue[idx++] = (yyvsp[0].exprtype)->getValue();
            Type* arrTy = stk.top()->getSymPtr()->getType();
            //到这里是最低维度
            if(arrTy == TypeSystem::intType)
                stk.top()->addExpr((yyvsp[0].exprtype));
            else//不是最低维度
                while(arrTy)
                {
                    //下一维度不是最低维度
                    if(((ArrayType*)arrTy)->getElementType() != TypeSystem::intType)
                    {
                        //获取这一维度的数组长度
                        arrTy = ((ArrayType*)arrTy)->getElementType();
                        SymbolEntry* se = new ConstantSymbolEntry(arrTy);
                        InitValueListExpr* list = new InitValueListExpr(se);
                        //赋值
                        stk.top()->addExpr(list);
                        stk.push(list);
                    }
                    else//下一维度是最低维度
                    {
                        //直接给栈顶赋值就好
                        stk.top()->addExpr((yyvsp[0].exprtype));
                        //全部出栈
                        while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt)
                        {
                            arrTy = ((ArrayType*)arrTy)->getArrayType();
                            stk.pop();
                        }
                        break;
                    }
                }
        }         
    }
#line 2709 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 996 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        ExprNode* list;
        if(stk.empty()){
            // 如果只用一个{}初始化数组，那么栈一定为空
            // 此时也没必要再加入栈了
            memset(arrayValue, 0, arrayType->getSize());
            idx += arrayType->getSize() / TypeSystem::intType->getSize();
            se = new ConstantSymbolEntry(arrayType);
            list = new InitValueListExpr(se);
        }
        else
        {
            // 栈不空说明肯定不是只有{}
            // 此时需要确定{}到底占了几个元素
            Type* type = ((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType();
            int len = type->getSize() / TypeSystem::intType->getSize();
            memset(arrayValue + idx, 0, type->getSize());
            idx += len;
            se = new ConstantSymbolEntry(type);
            list = new InitValueListExpr(se);
            stk.top()->addExpr(list);
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        }
        (yyval.exprtype) = list;
    }
#line 2742 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 1025 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        //栈不空则说明多个{}嵌套
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType());
        //获取的是值 4*2*i32
        se = new ConstantSymbolEntry(arrayType);
        //如果还有下一维数组
        if(arrayType->getElementType() != TypeSystem::intType)
        {
            //向下一维度
            arrayType = (ArrayType*)(arrayType->getElementType());
        }
        //
        InitValueListExpr* expr = new InitValueListExpr(se);
        //栈不空则设置一下值
        if(!stk.empty())
            stk.top()->addExpr(expr);
        //存入结果中
        stk.push(expr);
        (yyval.exprtype) = expr;
        leftCnt++;
    }
#line 2770 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 1048 "src/parser.y" /* yacc.c:1646  */
    {
        leftCnt--;
        
        while(stk.size() > (long unsigned int)(leftCnt + 1))
            stk.pop();
        if(stk.top() == (yyvsp[-2].exprtype))
            stk.pop();
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        if(!stk.empty())
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt)
            {
                stk.pop();
            }
        int size = ((ArrayType*)((yyval.exprtype)->getSymPtr()->getType()))->getSize()/ TypeSystem::intType->getSize();
        while(idx % size != 0)//未填充部分以0计
            arrayValue[idx++] = 0;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType());
    }
#line 2794 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 1070 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        if(!stk.empty()){
            arrayValue[idx++] = (yyvsp[0].exprtype)->getValue();
            Type* arrTy = stk.top()->getSymPtr()->getType();
            if(arrTy == TypeSystem::constIntType)
                stk.top()->addExpr((yyvsp[0].exprtype));
            else
                while(arrTy){
                    if(((ArrayType*)arrTy)->getElementType() != TypeSystem::constIntType){
                        arrTy = ((ArrayType*)arrTy)->getElementType();
                        SymbolEntry* se = new ConstantSymbolEntry(arrTy);
                        InitValueListExpr* list = new InitValueListExpr(se);
                        stk.top()->addExpr(list);
                        stk.push(list);
                    }else{
                        stk.top()->addExpr((yyvsp[0].exprtype));
                        while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                            arrTy = ((ArrayType*)arrTy)->getArrayType();
                            stk.pop();
                        }
                        break;
                    }
                }
        }
    }
#line 2825 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 1096 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        ExprNode* list;
        if(stk.empty()){
            // 如果只用一个{}初始化数组，那么栈一定为空
            // 此时也没必要再加入栈了
            memset(arrayValue, 0, arrayType->getSize());
            idx += arrayType->getSize() / TypeSystem::constIntType->getSize();
            se = new ConstantSymbolEntry(arrayType);
            list = new InitValueListExpr(se);
        }else{
            // 栈不空说明肯定不是只有{}
            // 此时需要确定{}到底占了几个元素
            Type* type = ((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType();
            int len = type->getSize() / TypeSystem::constIntType->getSize();
            memset(arrayValue + idx, 0, type->getSize());
            idx += len;
            se = new ConstantSymbolEntry(type);
            list = new InitValueListExpr(se);
            stk.top()->addExpr(list);
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        }
        (yyval.exprtype) = list;
    }
#line 2856 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 1122 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType());
        se = new ConstantSymbolEntry(arrayType);
        if(arrayType->getElementType() != TypeSystem::intType){
            arrayType = (ArrayType*)(arrayType->getElementType());
        }
        InitValueListExpr* expr = new InitValueListExpr(se);
        if(!stk.empty())
            stk.top()->addExpr(expr);
        stk.push(expr);
        (yyval.exprtype) = expr;
        leftCnt++;
    }
#line 2876 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 1137 "src/parser.y" /* yacc.c:1646  */
    {
        leftCnt--;
        while(stk.top() != (yyvsp[-2].exprtype) && stk.size() > (long unsigned int)(leftCnt + 1))
            stk.pop();
        if(stk.top() == (yyvsp[-2].exprtype))
            stk.pop();
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        if(!stk.empty())
            while(stk.top()->isFull() && stk.size() != (long unsigned int)leftCnt){
                stk.pop();
            }
        while(idx % (((ArrayType*)((yyval.exprtype)->getSymPtr()->getType()))->getSize()/ sizeof(int)) !=0 )
            arrayValue[idx++] = 0;
        if(!stk.empty())
            arrayType = (ArrayType*)(((ArrayType*)(stk.top()->getSymPtr()->getType()))->getElementType());
    }
#line 2897 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 1155 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2905 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 1158 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
    }
#line 2913 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 1163 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2921 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 1166 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
    }
#line 2929 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 1172 "src/parser.y" /* yacc.c:1646  */
    {
        // SymbolTable::resetLabel();
        identifiers = new SymbolTable(identifiers);
        paramNo = 0;
        //函数声明时假设为false
        if((yyvsp[-1].type)->isInt())
        {
            hasRet=false;
        }
    }
#line 2944 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 1182 "src/parser.y" /* yacc.c:1646  */
    {
        Type* funcType;
        std::vector<Type*> vec;
        std::vector<SymbolEntry*> vec1;
        DeclStmt* temp = (DeclStmt*)(yyvsp[-1].stmttype);
        while(temp){
            vec.push_back(temp->getId()->getSymPtr()->getType());
            vec1.push_back(temp->getId()->getSymPtr());
            temp = (DeclStmt*)(temp->getNext());
        }
        funcType = new FunctionType((yyvsp[-5].type), vec, vec1);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, (yyvsp[-4].strtype), identifiers->getPrev()->getLevel());
        //类型检查04：函数重定义
        if(!identifiers->getPrev()->install((yyvsp[-4].strtype), se))
        {
            fprintf(stderr, "函数\'%s\'重定义\n", (char*)(yyvsp[-4].strtype));
        }
        (yyval.se) = se; 
    }
#line 2968 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 1201 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = new FunctionDef((yyvsp[-1].se), (DeclStmt*)(yyvsp[-3].stmttype), (yyvsp[0].stmttype));
        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-6].strtype);
        //翻译完毕后即可检查是否有返回值
        if(hasRet==false)
        {
            fprintf(stderr, "int型函数 \" %s \" 缺少返回值\n",(char*)(yyvsp[-6].strtype));
            //恢复原值
            hasRet=true;
        }
    }
#line 2987 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 1218 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2993 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 1219 "src/parser.y" /* yacc.c:1646  */
    {(yyval.stmttype) = nullptr;}
#line 2999 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 1221 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyval.stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 3008 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 1225 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.stmttype) = (yyvsp[0].stmttype);
    }
#line 3016 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1231 "src/parser.y" /* yacc.c:1646  */
    {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel(), paramNo++);
        identifiers->install((yyvsp[0].strtype), se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 3030 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1240 "src/parser.y" /* yacc.c:1646  */
    {
        // 这里也需要求值
        SymbolEntry* se;
        ExprNode* temp = (yyvsp[0].exprtype);
        Type* arr = TypeSystem::intType;
        Type* arr1;
        std::stack<ExprNode*> stk;
        while(temp){
            stk.push(temp);
            temp = (ExprNode*)(temp->getNext());
        }
        while(!stk.empty()){
            arr1 = new ArrayType(arr, stk.top()->getValue());
            if(arr->isArray())
                ((ArrayType*)arr)->setArrayType(arr1);
            arr = arr1;
            stk.pop();
        }
        se = new IdentifierSymbolEntry(arr, (yyvsp[-1].strtype), identifiers->getLevel(), paramNo++);
        identifiers->install((yyvsp[-1].strtype), se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 3060 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1267 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = new ExprNode(nullptr);
    }
#line 3068 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1270 "src/parser.y" /* yacc.c:1646  */
    {
        (yyval.exprtype) = (yyvsp[-3].exprtype);
        (yyval.exprtype)->setNext((yyvsp[-1].exprtype));
    }
#line 3077 "src/parser.cpp" /* yacc.c:1646  */
    break;


#line 3081 "src/parser.cpp" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 1274 "src/parser.y" /* yacc.c:1906  */


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
