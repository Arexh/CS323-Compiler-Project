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




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

    #include"lex.yy.c"
    void yyerror(const char*);
    struct ASTNode *root;
    struct ASTNode *currentSpecifier;
    int structCheck;
    int structFather;
    int functionStart;
    int firstAssign;
    int functionCheck;
    struct ArrayList *conditionStack;
    struct ArrayList *jumpBlocksStack;
    struct ArrayList *whileIRStartStack;
    void RPError(const int);
    void SEMIError(const int);
    void STRUCTError(const int, const char *);
    void DEFError(const int);
    void initial();
    void fillJumpBlock();
    void fillFalseList();
    void fillTrueList();
    #define MAX_LINE 1024

#line 90 "syntax.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    ID = 261,
    TYPE = 262,
    STRUCT = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    RETURN = 267,
    DOT = 268,
    SEMI = 269,
    COMMA = 270,
    FOR = 271,
    ASSIGN = 272,
    LT = 273,
    LE = 274,
    GT = 275,
    GE = 276,
    NE = 277,
    EQ = 278,
    PLUS = 279,
    MINUS = 280,
    MUL = 281,
    DIV = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    LP = 286,
    RP = 287,
    LB = 288,
    RB = 289,
    LC = 290,
    RC = 291,
    INCLUDE = 292,
    UNKNOW = 293,
    BREAK = 294,
    CONTINUE = 295,
    WRITE = 296,
    READ = 297,
    HIGH_MINUS = 298,
    LOWER_ELSE = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "syntax.y" /* yacc.c:355  */

    struct ASTNode *node;

#line 179 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 210 "syntax.tab.c" /* yacc.c:358  */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   389

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    57,    61,    64,    68,    71,    76,    79,
      92,    99,   108,   113,   118,   128,   138,   147,   151,   155,
     159,   162,   166,   169,   186,   190,   194,   205,   209,   212,
     229,   240,   244,   247,   254,   257,   261,   269,   272,   281,
     284,   292,   295,   313,   316,   323,   331,   342,   352,   359,
     373,   380,   394,   397,   404,   407,   413,   420,   429,   443,
     447,   452,   456,   460,   464,   468,   472,   476,   480,   484,
     488,   492,   496,   499,   503,   506,   510,   514,   518,   521,
     525,   528,   532,   536,   540,   544,   548,   552,   555,   559,
     564,   568
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "ID", "TYPE",
  "STRUCT", "IF", "ELSE", "WHILE", "RETURN", "DOT", "SEMI", "COMMA", "FOR",
  "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ", "PLUS", "MINUS", "MUL",
  "DIV", "AND", "OR", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "INCLUDE",
  "UNKNOW", "BREAK", "CONTINUE", "WRITE", "READ", "HIGH_MINUS", "\"M2\"",
  "LOWER_ELSE", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "STRUCTTrigger", "VarDec", "FunDec",
  "FunID", "VarList", "ParamDec", "CompSt", "LCTrigger", "RCTrigger",
  "StmtList", "Stmt", "M1", "M2", "M3", "WHILETrigger", "ConditionExp",
  "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-30)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      65,   -53,   -53,    12,   -53,    65,    10,   -53,    11,   -53,
     -53,   -53,   -11,   -53,    21,   -10,    -4,    -2,    -1,   -53,
     -53,    69,    74,    57,   -53,    65,     7,    65,   -53,   -53,
      49,    65,    69,   115,    65,   -53,   -53,    69,     5,    76,
      58,   -53,   115,    53,    70,    86,   -53,   -53,   -53,    54,
      71,   -53,   106,   106,   106,   106,   -53,    89,    90,    77,
      83,   -53,    79,   115,    91,   148,   -53,    56,   -53,   -53,
      65,   -53,    87,   106,   -53,   -53,    69,    75,   106,   177,
      -6,    -6,   206,   -53,   -53,   106,    97,   -53,   -53,   -53,
     106,   -53,   124,   -53,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   -53,
     -53,   294,   -53,   -53,   -53,   228,     9,    27,   294,   -53,
     -53,   -53,   -53,   250,   -53,    35,   -53,   294,   351,   351,
     351,   351,   351,   351,   125,   125,    -6,    -6,   336,   315,
     272,    94,   106,   -53,   -53,   115,   -53,   -53,   115,   -53,
     -53,   -53,   131,   115,   -53,   115,   -53,   133,   -53,   115,
     -53,   -53,   115,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    12,    16,     0,     2,     4,     0,    13,     0,     1,
       3,     8,    17,     7,     0,    10,     0,     0,    15,     6,
       5,     0,     0,     0,     9,    52,     0,    52,    17,    11,
       0,    52,     0,    32,    52,    22,    21,     0,     0,    25,
       0,    18,    32,    57,     0,    55,    84,    85,    86,    83,
       0,    49,     0,     0,     0,     0,    87,     0,     0,     0,
       0,    35,     0,    32,     0,     0,    51,    26,    20,    19,
       0,    14,     0,     0,    54,    53,     0,     0,     0,     0,
      75,    76,     0,    44,    45,     0,     0,    30,    27,    31,
       0,    34,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      28,    58,    56,    80,    79,    91,     0,     0,    50,    37,
      36,    74,    73,     0,    88,     0,    82,    59,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    60,    61,
       0,    72,     0,    78,    77,     0,    46,    89,     0,    48,
      81,    90,    39,     0,    43,     0,    47,    38,    42,     0,
      47,    41,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   129,   -53,   138,     4,   -53,   -53,   -19,   -53,
     -53,   109,   -53,   144,   -53,   -53,   -23,   -20,   -53,    22,
     -53,   -53,    93,   153,   -53,    88,   -53,   -52,    43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    14,    32,     7,     8,    15,    16,
      17,    38,    39,    61,    25,    88,    62,    63,   153,   159,
     155,    64,   117,    33,    34,    44,    45,    65,   116
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    80,    81,    82,     6,    21,    68,    92,    35,     6,
     143,    11,     9,    43,     1,     2,    12,    18,    67,    72,
     -23,   111,    19,    22,    13,   115,   118,   107,   145,    26,
      37,    23,   108,   123,    27,    20,   148,    69,   118,    36,
      89,   144,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    43,    31,   146,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   149,   -29,   -29,
      73,    74,     1,     2,    37,    28,   113,    30,    46,    47,
      48,    49,   -29,    41,    75,    77,    22,   -29,   -29,    22,
     115,    70,   -29,   -29,    71,   -29,   -29,   -29,   -29,   -29,
      53,    76,    78,    83,    84,    54,    55,   114,    85,    46,
      47,    48,    49,    56,    86,    87,    59,    60,    46,    47,
      48,    49,    90,   110,    50,   152,    51,    52,   154,   124,
     126,    53,   -30,   157,    10,   158,    54,    55,    92,   161,
      53,   156,   163,   160,    56,    54,    55,    59,    60,    91,
      23,   103,   104,    56,    57,    58,    59,    60,   107,    29,
      24,    92,    93,   108,   112,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   119,   109,
      40,   107,   162,   125,    42,   151,   108,    66,     0,     0,
      92,   120,     0,     0,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   121,     0,     0,
     107,     0,     0,     0,     0,   108,     0,     0,     0,    92,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,   122,   107,
       0,    92,     0,   142,   108,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,   107,     0,    92,     0,     0,   108,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,     0,   147,   107,     0,    92,     0,     0,   108,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,     0,     0,   107,   150,    92,     0,     0,
     108,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,   107,    92,     0,
       0,     0,   108,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,   107,    92,
       0,     0,     0,   108,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,    92,     0,     0,     0,     0,   107,
       0,     0,     0,     0,   108,   101,   102,   103,   104,     0,
       0,     0,     0,     0,   107,     0,     0,     0,     0,   108
};

static const yytype_int16 yycheck[] =
{
      52,    53,    54,    55,     0,    15,     1,    13,     1,     5,
       1,     1,     0,    32,     7,     8,     6,     6,    37,    42,
      31,    73,     1,    33,    14,    77,    78,    33,     1,    31,
      26,    35,    38,    85,    35,    14,     1,    32,    90,    32,
      63,    32,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,    76,     1,    32,
       3,     4,     5,     6,     7,     8,     9,    32,    11,    12,
      17,     1,     7,     8,    70,     6,     1,     3,     3,     4,
       5,     6,    25,    34,    14,    31,    33,    30,    31,    33,
     142,    15,    35,    36,    36,    38,    39,    40,    41,    42,
      25,    15,    31,    14,    14,    30,    31,    32,    31,     3,
       4,     5,     6,    38,    31,    36,    41,    42,     3,     4,
       5,     6,    31,    36,     9,   145,    11,    12,   148,    32,
       6,    25,    38,   153,     5,   155,    30,    31,    13,   159,
      25,    10,   162,    10,    38,    30,    31,    41,    42,     1,
      35,    26,    27,    38,    39,    40,    41,    42,    33,    21,
      16,    13,    14,    38,    76,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     1,    70,
      27,    33,   160,    90,    31,   142,    38,    34,    -1,    -1,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    13,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      -1,    13,    -1,    15,    38,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    33,    -1,    13,    -1,    -1,    38,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    -1,    13,    -1,    -1,    38,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    33,    34,    13,    -1,    -1,
      38,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    33,    13,    -1,
      -1,    -1,    38,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,    13,
      -1,    -1,    -1,    38,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    13,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    47,    48,    49,    51,    52,    53,     0,
      48,     1,     6,    14,    50,    54,    55,    56,     6,     1,
      14,    15,    33,    35,    59,    60,    31,    35,     6,    50,
       3,     1,    51,    69,    70,     1,    32,    51,    57,    58,
      69,    34,    69,    54,    71,    72,     3,     4,     5,     6,
       9,    11,    12,    25,    30,    31,    38,    39,    40,    41,
      42,    59,    62,    63,    67,    73,    69,    54,     1,    32,
      15,    36,    62,    17,     1,    14,    15,    31,    31,    73,
      73,    73,    73,    14,    14,    31,    31,    36,    61,    62,
      31,     1,    13,    14,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    33,    38,    57,
      36,    73,    71,     1,    32,    73,    74,    68,    73,     1,
      14,     1,    32,    73,    32,    68,     6,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    15,     1,    32,     1,    32,    32,     1,    32,
      34,    74,    63,    64,    63,    66,    10,    63,    63,    65,
      10,    63,    65,    63
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    54,    54,    55,
      55,    55,    55,    56,    57,    57,    58,    59,    59,    60,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    65,    66,    67,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     2,     2,     3,
       1,     3,     1,     1,     5,     2,     1,     1,     4,     4,
       4,     3,     3,     1,     3,     1,     2,     4,     5,     1,
       1,     2,     0,     2,     2,     1,     3,     3,     6,     5,
       9,     8,     6,     5,     2,     2,     0,     0,     0,     1,
       1,     2,     0,     3,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     4,     3,
       3,     4,     3,     1,     1,     1,     1,     1,     3,     4,
       3,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
     '$$ = $1'.

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
#line 52 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Program", (yyloc).first_line); 
        root = (yyval.node);
        appendChild((yyval.node), 1, (yyvsp[0].node)); 
     }
#line 1546 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 57 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDefList", (yylsp[-1]).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 1555 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 61 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
    }
#line 1563 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 64 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDef", (yyloc).first_line);
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1572 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 68 "syntax.y" /* yacc.c:1646  */
    {
        SEMIError((yyloc).first_line);
    }
#line 1580 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 71 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDef", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        put_struct_specifier(currentSpecifier);
    }
#line 1590 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 76 "syntax.y" /* yacc.c:1646  */
    {
        SEMIError((yyloc).first_line);
    }
#line 1598 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 79 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDef", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            // function end
            if (currentFunction->re == 0) {
                fprintf(out, "Error at Line %d: function has no return value", (yyloc).first_line);
            }
            function_stack_pop();
            hash_table_stack_pop();
        }
        functionCheck = 0;
    }
#line 1616 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 92 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDecList", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
        // put varDec
        put_var(currentSpecifier, (yyvsp[0].node));
        // IR var num allocation finish
    }
#line 1628 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 99 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ExtDecList", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        // put varDec
        put_var(currentSpecifier, (yyvsp[-2].node));
        // IR var num allocation finish
    }
#line 1640 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 108 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Specifier", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
        currentSpecifier = (yyvsp[0].node);
    }
#line 1650 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 113 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Specifier", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
        currentSpecifier = (yyvsp[0].node);
    }
#line 1660 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 118 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("StructSpecifier", (yyloc).first_line); 
        appendChild((yyval.node), 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        if (structFather) {
            structCheck = 1;
            structFather = 0;
        } else {
            structCheck = 0; 
        }
    }
#line 1675 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 128 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("StructSpecifier", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (structFather) {
            structCheck = 1;
            structFather = 0;
        } else {
            structCheck = 0;
        }
    }
#line 1690 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 138 "syntax.y" /* yacc.c:1646  */
    {
        if (structCheck) {
            structFather = 1;
        } else {
            structCheck = 1;
        }
        (yyval.node) = (yyvsp[0].node);
    }
#line 1703 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 147 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarDec", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
    }
#line 1712 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 151 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarDec", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1721 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 155 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("FunDec", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1730 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 159 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 1738 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("FunDec", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1747 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 166 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 1755 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 169 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("FunID", (yyloc).first_line);
        appendChild((yyval.node), 1, (yyvsp[0].node));
        // function start
        functionCheck = function_stack_push(currentSpecifier, (yyvsp[0].node)->value, (yyloc).first_line);
        if (functionCheck == 0) {
            currentScopeNumber++;
            hash_table_stack_push(currentFunction->hashTable);
            functionStart = 1;
            // function IR start
            IRInstruct *func_instruct = append_new_instruct(blockEnd);
            func_instruct->funcName = (char *)(yyvsp[0].node)->value;
            func_instruct->type = _FUNCTION;
            append_new_block();
            // IR end
        }
    }
#line 1777 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 186 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarList", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1786 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 190 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("VarList", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
    }
#line 1795 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 194 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("ParamDec", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            // parameter IR start
            put_para((yyvsp[-1].node)->child[0], (yyvsp[0].node));
            // IR end
        }
    }
#line 1809 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 205 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("CompSt", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1818 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 209 "syntax.y" /* yacc.c:1646  */
    {
        DEFError((yylsp[-3]).first_line);
    }
#line 1826 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 212 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
        if (functionCheck == 0) {
            if (functionStart == 0) {
                if (currentSymbolTable == NULL) {
                    currentSymbolTable = new_symbol_table();
                } else {
                    SymbolTable *symbolTable = new_symbol_table();
                    symbolTable->next = currentSymbolTable;
                    currentSymbolTable = symbolTable;
                }
                currentScopeNumber++;
            } else {
                functionStart = 0;
            }
        }
    }
#line 1848 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 229 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
        if (functionCheck == 0) {
            SymbolTable *remove = currentSymbolTable;
            if (remove) {
                currentSymbolTable = currentSymbolTable->next;
                symbol_table_remove(currentTable, remove);
            }
            currentScopeNumber--;
        }
    }
#line 1864 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 240 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("StmtList", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1873 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 244 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
    }
#line 1881 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 247 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            check_exp((yyvsp[-1].node));
        }
    }
#line 1893 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 254 "syntax.y" /* yacc.c:1646  */
    {
        SEMIError((yyloc).first_line);
    }
#line 1901 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 257 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
    }
#line 1910 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 261 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            check_return_exp((yyvsp[-1].node));
            currentFunction->re = 1;
        }
    }
#line 1923 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 269 "syntax.y" /* yacc.c:1646  */
    {
        SEMIError((yyloc).first_line);
    }
#line 1931 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 272 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 5, (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
        // end of condition
        append_new_block();
        fillJumpBlock();
        fillFalseList();
        // IR end
    }
#line 1945 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 281 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 1953 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 284 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 7, (yyvsp[-8].node), (yyvsp[-7].node), (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node));
        // end of if IR start
        append_new_block();
        fillJumpBlock();
        // IR end
    }
#line 1966 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 292 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 1974 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 295 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 5, (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
        if (currentLoop) {
            LoopStack *temp = currentLoop;
            currentLoop = currentLoop->next;
            temp->next = NULL;
            free(temp);
        }
        // end of while IR start
        IRBlock *before = blockEnd;
        append_new_block();
        IRBlock *whileIRStart = get_last_from_array_list(whileIRStartStack);
        before->next = whileIRStart;
        whileIRStartStack->memberNum--;
        fillFalseList();
        // IR end
    }
#line 1997 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 313 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 2005 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 316 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (currentLoop == NULL) {
            fprintf(out, "Error at Line %d: break is used outside loop\n", (yyloc).first_line);
        }
    }
#line 2017 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 323 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Stmt", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (currentLoop == NULL) {
            fprintf(out, "Error at Line %d: continue is used outside loop\n", (yyloc).first_line);
        }
    }
#line 2029 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 331 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
        // true jump IR start
        append_new_block();
        ArrayList *jumpBlocks = new_array_list();
        append_to_array_list(jumpBlocksStack, jumpBlocks);
        append_to_array_list(jumpBlocks, blockEnd);
        fillTrueList();
        // IR end
    }
#line 2044 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 342 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
        // false jump IR start
        append_new_block();
        ArrayList *jumpBlocks = get_last_from_array_list(jumpBlocksStack);
        append_to_array_list(jumpBlocks, blockEnd);
        fillFalseList();
        // IR end
    }
#line 2058 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 352 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
        // true jump in while IR start
        append_new_block();
        fillTrueList();
        // IR end
    }
#line 2070 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 359 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
        if (currentLoop == NULL) {
            currentLoop = new_loop_stack();
        } else {
            LoopStack *newLoop = new_loop_stack();
            newLoop->next = currentLoop;
            currentLoop = newLoop;
        }
        // while start IR start
        append_new_block();
        append_to_array_list(whileIRStartStack, blockEnd);
        // IR end
    }
#line 2089 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 373 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[0].node);
        if (functionCheck == 0) {
            append_to_array_list(conditionStack, check_condition((yyvsp[0].node)));
        }
    }
#line 2100 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 380 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DefList", (yyloc).first_line);
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            if (strcmp((yyvsp[0].node)->type, "NONE") == 0) {
                (yyval.node)->value = malloc(sizeof(int));
                *(int *)(yyval.node)->value = *(int*)(yyvsp[-1].node)->value + 0;
            } else {
                (yyval.node)->value = malloc(sizeof(int));
                memcpy((yyval.node)->value, (yyvsp[0].node)->value, sizeof(int));
                *(int*)(yyval.node)->value = *(int *)(yyval.node)->value + *(int *)(yyvsp[-1].node)->value;
            }
        }
    }
#line 2119 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 394 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("NONE", (yyloc).first_line);
    }
#line 2127 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 397 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Def", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        if (functionCheck == 0) {
            (yyval.node)->value = (yyvsp[-1].node)->value;
        }
    }
#line 2139 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 404 "syntax.y" /* yacc.c:1646  */
    {
        SEMIError((yyloc).first_line);
    }
#line 2147 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 407 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DecList", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
        (yyval.node)->value = malloc(sizeof(int));
        *((int *)(yyval.node)->value) = 1;
    }
#line 2158 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 413 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("DecList", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node)->value = malloc(sizeof(int));
        *((int *)(yyval.node)->value) = *((int *)(yyvsp[0].node)->value) + 1;
    }
#line 2169 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 420 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Dec", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
        if (structCheck == 0) {
            // put varDec
            put_var(currentSpecifier, (yyvsp[0].node));
            // IR var num allocation
        }
    }
#line 2183 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 429 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Dec", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
        if (structCheck == 0) {
            // put varDec
            int re = put_var(currentSpecifier, (yyvsp[-2].node));
            // IR var num allocation
            if (re == 0) {
                // assign check here
                check_assign_exp((yyvsp[-2].node), (yyvsp[0].node));
            }
        }
    }
#line 2201 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 443 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2210 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 448 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2219 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 452 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2228 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 456 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2237 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 460 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2246 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 464 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2255 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 468 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2264 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 472 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2273 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 476 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2282 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 480 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2291 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 484 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2300 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 488 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2309 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 492 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2318 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 496 "syntax.y" /* yacc.c:1646  */
    {
        STRUCTError((yyloc).first_line, (yyvsp[-1].node)->value);
    }
#line 2326 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 499 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2335 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 503 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 2343 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 506 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2352 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 510 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 2, (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2361 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 514 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2370 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 518 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 2378 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 521 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2387 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 525 "syntax.y" /* yacc.c:1646  */
    {
        RPError((yyloc).first_line);
    }
#line 2395 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 528 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2404 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 532 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2413 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 536 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        appendChild((yyval.node), 1, (yyvsp[0].node));
    }
#line 2422 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 540 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        appendChild((yyval.node), 1, (yyvsp[0].node)); 
    }
#line 2431 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 544 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node));
    }
#line 2440 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 548 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Exp", (yyloc).first_line);
        appendChild((yyval.node), 1, (yyvsp[0].node)); 
    }
#line 2449 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 552 "syntax.y" /* yacc.c:1646  */
    {

    }
#line 2457 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 555 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2466 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 559 "syntax.y" /* yacc.c:1646  */
    {
        (yyval.node) = newNode("Exp", (yyloc).first_line); 
        appendChild((yyval.node), 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2475 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 564 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Args", (yyloc).first_line); 
        appendChild((yyval.node), 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 2484 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 568 "syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node) = newNode("Args", (yyloc).first_line); 
        appendChild((yyval.node), 1, (yyvsp[0].node)); 
    }
#line 2493 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2497 "syntax.tab.c" /* yacc.c:1646  */
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 573 "syntax.y" /* yacc.c:1906  */

void fillTrueList() {
    TypeCheck *conditionType = get_last_from_array_list(conditionStack);
    ArrayList *trueList = conditionType->trueList;
    if (trueList) {
        back_patching_true_list(trueList, blockEnd);
        free_array_list(conditionType->trueList);
    }
    conditionType->trueList = NULL;
}
void fillFalseList() {
    TypeCheck *conditionType = get_last_from_array_list(conditionStack);
    ArrayList *falseList = conditionType->falseList;
    if (falseList) {
        back_patching_false_list(falseList, blockEnd);
        free_array_list(conditionType->falseList);
    }
    conditionType->falseList = NULL;
    conditionStack->memberNum--;
}
void fillJumpBlock() {
    ArrayList *jumpBlocks = get_last_from_array_list(jumpBlocksStack);
    back_patching_true_list(jumpBlocks, blockEnd);
    free_array_list(jumpBlocks);
    jumpBlocksStack->memberNum--;
}
void RPError(const int lineno){
    fprintf(out, "Error type B at Line %d: Missing closing parenthesis ')'\n", lineno);
    error = 1;
}
void SEMIError(const int lineno){
    fprintf(out, "Error type B at Line %d: Missing semicolon ';'\n", lineno);
    error = 1;
}
void STRUCTError(const int lineno, const char *text){
    fprintf(out, "Error type B at Line %d: Unknow operator %s\n", lineno, text);
    error = 1;
}
void DEFError(const int lineno){
    fprintf(out, "Error type B at Line %d: Invalid Definition\n", lineno);
    error = 1;
}
void yyerror(const char *s){
    // fprintf(out, "%s", s);
}
void initial(){
    yycolno = 1;
    yylineno = 1;
    yytext = "";
    yyleng = 0;
    error = 0;
    wrong = 0;
    rec = "";
    head = NULL;
    node = NULL;
    neasted_start = 0;
    root = NULL;
    currentTable = new_hash_table();
    currentScopeNumber = 0;
    structCheck = 0;
    structFather = 0;
    firstAssign = 0;
    functionStart = 0;
    functionCheck = 0;
    init_number_control();
    init_IR_block();
    conditionStack = new_array_list();
    jumpBlocksStack = new_array_list();
    whileIRStartStack = new_array_list();
}
#ifndef CALC_MAIN
#else
int main(int count, char **args){
    if (count == 1){
        initial();
        out = stdout;
        yyparse();
        // if (error == 0) {
        //     dfsPrintf(root, 0);
        // }
        printf_all_blocks();
    } else {
        for(int x = 1; x < count; x++){
            initial();
            int length = strlen(args[x]);
            char *output = malloc(length + 1);
            strcpy(output, args[x]);
            output[length] = 0;
            output[length - 1] = 't';
            output[length - 2] = 'u';
            output[length - 3] = 'o';
            char buf[MAX_LINE];
            int len;
            if ((fp = fopen(args[x],"r")) == NULL)
            {
                perror("fail to read");
                exit (1) ;
            }
            out = fopen(output, "w");
            yyrestart(fp);
            yyparse();
            // if (error == 0)
            //     dfsPrintf(root, 0);
            fclose(fp);
            fclose(out);
        }        
        return 0;
    }
    
}
#endif

int evaluate(char *expr){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(expr);
    yyparse();
    yy_delete_buffer(buf);
    return 0;
}
