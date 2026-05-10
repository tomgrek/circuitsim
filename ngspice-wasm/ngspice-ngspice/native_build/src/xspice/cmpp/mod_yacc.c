/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "../../../../src/xspice/cmpp/mod_yacc.y"


/*============================================================================
FILE  mod_yacc.y

MEMBER OF process cmpp

Copyright 1991
Georgia Tech Research Corporation
Atlanta, Georgia 30332
All Rights Reserved

PROJECT A-8503

AUTHORS

    9/12/91  Steve Tynor

MODIFICATIONS

    <date> <person name> <nature of modifications>
  20050420 Steven Borley Renamed strcmpi() to local_strcmpi() to avoid
                         clash with strcmpi() in a windows header file.

SUMMARY

    This file contains a BNF specification of the translation of
    cfunc.mod files to cfunc.c files, together with various support
    functions.

INTERFACES

    mod_yyparse() -    Function 'yyparse()' is generated automatically
                       by UNIX 'yacc' utility.  All yy* global names
                       are converted to mod_yy* by #define.

REFERENCED FILES

    mod_lex.l

============================================================================*/


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mod_yacc_y.h"

extern int mod_yylex(void);

#define	yymaxdepth mod_yymaxdepth
#define	yyparse	mod_yyparse
#define	yylex	mod_yylex
#define	yyerror	mod_yyerror
#define	yylval	mod_yylval
#define	yychar	mod_yychar
#define	yydebug	mod_yydebug
#define	yypact	mod_yypact
#define	yyr1	mod_yyr1
#define	yyr2	mod_yyr2
#define	yydef	mod_yydef
#define	yychk	mod_yychk
#define	yypgo	mod_yypgo
#define	yyact	mod_yyact
#define	yyexca	mod_yyexca
#define yyerrflag mod_yyerrflag
#define yynerrs	mod_yynerrs
#define	yyps	mod_yyps
#define	yypv	mod_yypv
#define	yys	mod_yys
#define	yy_yys	mod_yyyys
#define	yystate	mod_yystate
#define	yytmp	mod_yytmp
#define	yyv	mod_yyv
#define	yy_yyv	mod_yyyyv
#define	yyval	mod_yyval
#define	yylloc	mod_yylloc
#define yyreds	mod_yyreds
#define yytoks	mod_yytoks
#define yylhs	mod_yyyylhs
#define yylen	mod_yyyylen
#define yydefred mod_yyyydefred
#define yydgoto	mod_yyyydgoto
#define yysindex mod_yyyysindex
#define yyrindex mod_yyyyrindex
#define yygindex mod_yyyygindex
#define yytable	 mod_yyyytable
#define yycheck	 mod_yyyycheck
#define yyname   mod_yyyyname
#define yyrule   mod_yyyyrule

Ifs_Table_t *mod_ifs_table;

extern char *mod_yytext;
extern FILE* mod_yyout;

#include <string.h>
#include <ctype.h>

int mod_num_errors;

#define BUFFER_SIZE 3000
static char buffer [BUFFER_SIZE];
static int buf_len;
   
typedef enum {CONN, PARAM, STATIC_VAR} Id_Kind_t;

/*--------------------------------------------------------------------------*/
static char *subscript (Sub_Id_t sub_id)
{
   if (sub_id.has_subscript) {
      return sub_id.subscript;
   } else {
      return "0";
   }
}

/*--------------------------------------------------------------------------*/
static int
local_strcmpi(char *s, char *t)
     /* string compare -  case insensitive */
{
   for (; *s && t && tolower_c(*s) == tolower_c(*t); s++, t++)
      ;
   if (*s && !*t) {
      return 1;
   }
   if (!*s && *t) {
      return -1;
   }
   if (! (*s || *t)) {
      return 0;
   }
   return tolower((unsigned char) *s) - tolower((unsigned char) *t);
}

/*---------------------------------------------------------------------------*/
static void put_type (FILE *fp, Data_Type_t type)
{
   char ch = ' ';
   
   switch (type) {
   case CMPP_INTEGER:
      ch = 'i';
      break;
   case CMPP_REAL:
      ch = 'r';
      break;
   case CMPP_COMPLEX:
      ch = 'c';
      break;
   case CMPP_BOOLEAN:
      ch = 'b';
      break;
   case CMPP_STRING:
      ch = 's';
      break;
   case CMPP_POINTER:
      ch = 'p';
      break;
   }
   fprintf (fp, ".%cvalue", ch);
}

/*---------------------------------------------------------------------------*/
static void put_conn_type (FILE *fp, Port_Type_t type)
{
   char ch;
   
   switch (type) {
   case USER_DEFINED:
      ch = 'p';
      break;
   case DIGITAL:
      ch = 'p';
      break;
   default:
      ch = 'r';
      break;
   }
   fprintf (fp, ".%cvalue", ch);
}

/*---------------------------------------------------------------------------*/
static void check_dir (int conn_number, Dir_t dir, char *context)
{
   Dir_t conn_dir;
   
   if (conn_number >= 0) {
      /*
       * If negative, this is an invalid port ID and we've already issued
       * an error.
       */
      conn_dir = mod_ifs_table->conn[conn_number].direction;
      if ((conn_dir != dir) && (conn_dir != CMPP_INOUT)) {
	 char error_str[200];
	 
	 sprintf (error_str,
		  "Direction of port `%s' in %s() is not %s or INOUT",
		  mod_ifs_table->conn[conn_number].name, context,
		  (dir == CMPP_IN) ? "IN" : "OUT");
	 yyerror (error_str);
	 mod_num_errors++;
      }
   }
}

/*---------------------------------------------------------------------------*/
static void check_subscript (bool formal, bool actual,
			     bool missing_actual_ok,
			     char *context, char *id)
{
   char error_str[200];

   if ((formal && !actual) && !missing_actual_ok) {
      sprintf (error_str,
	       "%s `%s' is an array - subscript required",
	       context, id);
      yyerror (error_str);
      mod_num_errors++;
      return;
   } else if (!formal && actual) {
      sprintf (error_str,
	       "%s `%s' is not an array - subscript prohibited",
	       context, id);
      yyerror (error_str);
      mod_num_errors++;
      return;
   }
}

/*---------------------------------------------------------------------------*/
static int check_id (Sub_Id_t sub_id, Id_Kind_t kind, bool do_subscript)
{
   int i;
   char error_str[200];
   
   switch (kind) {
   case CONN:
      for (i = 0; i < mod_ifs_table->num_conn; i++) {
	 if (0 == local_strcmpi (sub_id.id, mod_ifs_table->conn[i].name)) {
	    if (do_subscript) {
	       check_subscript (mod_ifs_table->conn[i].is_array,
				sub_id.has_subscript, false, "Port",
				sub_id.id);
	    }
	    return i;
	 }
      }
      break;
   case PARAM:
      for (i = 0; i < mod_ifs_table->num_param; i++) {
      	 if (0 == local_strcmpi (sub_id.id, mod_ifs_table->param[i].name)) {
	    if (do_subscript) {
	       check_subscript (mod_ifs_table->param[i].is_array,
				sub_id.has_subscript, false, "Parameter",
				sub_id.id);
	    }
	    return i;
	 }
      }
      break;
   case STATIC_VAR:
      for (i = 0; i < mod_ifs_table->num_inst_var; i++) {
      	 if (0 == local_strcmpi (sub_id.id, mod_ifs_table->inst_var[i].name)) {
	    if (do_subscript) {
	       check_subscript (mod_ifs_table->inst_var[i].is_array,
				sub_id.has_subscript, true,
				"Static Variable",
				sub_id.id);
	    }
	    return i;
	 }
      }
      break;
   }
   
   sprintf (error_str, "No %s named '%s'",
	    ((kind==CONN)
	     ? "port"
	     : ((kind==PARAM)
		? "parameter"
		:"static variable")),
	    sub_id.id);
   yyerror (error_str);
   mod_num_errors++;
   return -1;
}

/*---------------------------------------------------------------------------*/
static int valid_id (Sub_Id_t sub_id, Id_Kind_t kind)
{
    return check_id (sub_id, kind, false);
}

/*---------------------------------------------------------------------------*/
static int valid_subid (Sub_Id_t sub_id, Id_Kind_t kind)
{
    return check_id (sub_id, kind, true);
}

/*---------------------------------------------------------------------------*/
static void init_buffer (void)
{
   buf_len = 0;
   buffer[0] = '\0';
}

/*---------------------------------------------------------------------------*/
static void append (char *str)
{
   int len = (int) strlen (str);
   if (len + buf_len > BUFFER_SIZE) {
      yyerror ("Buffer overflow - try reducing the complexity of CM-macro array subscripts");
      exit (1);
   }
   (void)strcat (buffer,str);
}


#line 393 "mod_yacc.c"

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

#include "mod_yacc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_ARGS = 3,                   /* TOK_ARGS  */
  YYSYMBOL_TOK_INIT = 4,                   /* TOK_INIT  */
  YYSYMBOL_TOK_CALLBACK = 5,               /* TOK_CALLBACK  */
  YYSYMBOL_TOK_ANALYSIS = 6,               /* TOK_ANALYSIS  */
  YYSYMBOL_TOK_NEW_TIMEPOINT = 7,          /* TOK_NEW_TIMEPOINT  */
  YYSYMBOL_TOK_TIME = 8,                   /* TOK_TIME  */
  YYSYMBOL_TOK_RAD_FREQ = 9,               /* TOK_RAD_FREQ  */
  YYSYMBOL_TOK_TEMPERATURE = 10,           /* TOK_TEMPERATURE  */
  YYSYMBOL_TOK_T = 11,                     /* TOK_T  */
  YYSYMBOL_TOK_PARAM = 12,                 /* TOK_PARAM  */
  YYSYMBOL_TOK_PARAM_SIZE = 13,            /* TOK_PARAM_SIZE  */
  YYSYMBOL_TOK_PARAM_NULL = 14,            /* TOK_PARAM_NULL  */
  YYSYMBOL_TOK_PORT_SIZE = 15,             /* TOK_PORT_SIZE  */
  YYSYMBOL_TOK_PORT_NULL = 16,             /* TOK_PORT_NULL  */
  YYSYMBOL_TOK_PARTIAL = 17,               /* TOK_PARTIAL  */
  YYSYMBOL_TOK_AC_GAIN = 18,               /* TOK_AC_GAIN  */
  YYSYMBOL_TOK_CHANGED = 19,               /* TOK_CHANGED  */
  YYSYMBOL_TOK_OUTPUT_DELAY = 20,          /* TOK_OUTPUT_DELAY  */
  YYSYMBOL_TOK_STATIC_VAR = 21,            /* TOK_STATIC_VAR  */
  YYSYMBOL_TOK_STATIC_VAR_SIZE = 22,       /* TOK_STATIC_VAR_SIZE  */
  YYSYMBOL_TOK_STATIC_VAR_INST = 23,       /* TOK_STATIC_VAR_INST  */
  YYSYMBOL_TOK_INPUT = 24,                 /* TOK_INPUT  */
  YYSYMBOL_TOK_INPUT_STRENGTH = 25,        /* TOK_INPUT_STRENGTH  */
  YYSYMBOL_TOK_INPUT_STATE = 26,           /* TOK_INPUT_STATE  */
  YYSYMBOL_TOK_INPUT_TYPE = 27,            /* TOK_INPUT_TYPE  */
  YYSYMBOL_TOK_OUTPUT = 28,                /* TOK_OUTPUT  */
  YYSYMBOL_TOK_OUTPUT_CHANGED = 29,        /* TOK_OUTPUT_CHANGED  */
  YYSYMBOL_TOK_OUTPUT_STRENGTH = 30,       /* TOK_OUTPUT_STRENGTH  */
  YYSYMBOL_TOK_OUTPUT_STATE = 31,          /* TOK_OUTPUT_STATE  */
  YYSYMBOL_TOK_OUTPUT_TYPE = 32,           /* TOK_OUTPUT_TYPE  */
  YYSYMBOL_TOK_COMMA = 33,                 /* TOK_COMMA  */
  YYSYMBOL_TOK_LPAREN = 34,                /* TOK_LPAREN  */
  YYSYMBOL_TOK_RPAREN = 35,                /* TOK_RPAREN  */
  YYSYMBOL_TOK_LBRACKET = 36,              /* TOK_LBRACKET  */
  YYSYMBOL_TOK_RBRACKET = 37,              /* TOK_RBRACKET  */
  YYSYMBOL_TOK_MISC_C = 38,                /* TOK_MISC_C  */
  YYSYMBOL_TOK_IDENTIFIER = 39,            /* TOK_IDENTIFIER  */
  YYSYMBOL_TOK_LOAD = 40,                  /* TOK_LOAD  */
  YYSYMBOL_TOK_TOTAL_LOAD = 41,            /* TOK_TOTAL_LOAD  */
  YYSYMBOL_TOK_MESSAGE = 42,               /* TOK_MESSAGE  */
  YYSYMBOL_TOK_CALL_TYPE = 43,             /* TOK_CALL_TYPE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_mod_file = 45,                  /* mod_file  */
  YYSYMBOL_c_code = 46,                    /* c_code  */
  YYSYMBOL_buffered_c_code = 47,           /* buffered_c_code  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_buffered_c_code2 = 49,          /* buffered_c_code2  */
  YYSYMBOL_buffered_c_char = 50,           /* buffered_c_char  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_c_char = 53,                    /* c_char  */
  YYSYMBOL_54_4 = 54,                      /* $@4  */
  YYSYMBOL_55_5 = 55,                      /* $@5  */
  YYSYMBOL_macro = 56,                     /* macro  */
  YYSYMBOL_subscriptable_id = 57,          /* subscriptable_id  */
  YYSYMBOL_id = 58                         /* id  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   377,   377,   378,   381,   382,   383,   384,   385,   388,
     388,   392,   393,   396,   397,   398,   400,   399,   404,   403,
     409,   410,   411,   412,   414,   413,   417,   419,   418,   424,
     426,   428,   430,   432,   434,   436,   438,   440,   442,   444,
     450,   453,   456,   459,   462,   470,   479,   491,   495,   499,
     505,   511,   519,   525,   531,   540,   549,   557,   566,   575,
     580,   585,   590,   597,   598,   604
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_ARGS", "TOK_INIT",
  "TOK_CALLBACK", "TOK_ANALYSIS", "TOK_NEW_TIMEPOINT", "TOK_TIME",
  "TOK_RAD_FREQ", "TOK_TEMPERATURE", "TOK_T", "TOK_PARAM",
  "TOK_PARAM_SIZE", "TOK_PARAM_NULL", "TOK_PORT_SIZE", "TOK_PORT_NULL",
  "TOK_PARTIAL", "TOK_AC_GAIN", "TOK_CHANGED", "TOK_OUTPUT_DELAY",
  "TOK_STATIC_VAR", "TOK_STATIC_VAR_SIZE", "TOK_STATIC_VAR_INST",
  "TOK_INPUT", "TOK_INPUT_STRENGTH", "TOK_INPUT_STATE", "TOK_INPUT_TYPE",
  "TOK_OUTPUT", "TOK_OUTPUT_CHANGED", "TOK_OUTPUT_STRENGTH",
  "TOK_OUTPUT_STATE", "TOK_OUTPUT_TYPE", "TOK_COMMA", "TOK_LPAREN",
  "TOK_RPAREN", "TOK_LBRACKET", "TOK_RBRACKET", "TOK_MISC_C",
  "TOK_IDENTIFIER", "TOK_LOAD", "TOK_TOTAL_LOAD", "TOK_MESSAGE",
  "TOK_CALL_TYPE", "$accept", "mod_file", "c_code", "buffered_c_code",
  "$@1", "buffered_c_code2", "buffered_c_char", "$@2", "$@3", "c_char",
  "$@4", "$@5", "macro", "subscriptable_id", "id", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -122,     5,  -122,  -122,  -122,   142,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,   -28,    -3,     4,     7,    11,    18,
      20,    23,    24,    25,    26,    63,   102,   143,   145,   152,
     153,   154,   155,   156,   157,   158,  -122,   159,     2,  -122,
    -122,   161,   162,   163,  -122,  -122,  -122,  -122,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,  -122,
      -1,  -122,    -1,   160,   160,   160,   165,  -122,  -122,   166,
     167,   169,   170,   171,   172,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,    60,   101,   191,   192,   193,  -122,    17,  -122,  -122,
    -122,  -122,  -122,  -122,   160,   160,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,   173,   194,   195,  -122,  -122,  -122,  -122,  -122,    -6,
      10,  -122,  -122
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     4,     1,     7,     8,     3,    31,    29,    30,    32,
      33,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    27,    24,    21,
      20,     0,     0,     0,    34,     5,     6,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       4,    23,     4,     0,     0,     0,     0,    11,    65,     0,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    10,    39,     9,
      40,    41,    42,    43,     0,     0,    50,    49,    46,    47,
      48,    51,    54,    55,    52,    56,    59,    57,    58,    53,
      28,    25,    60,    61,    62,    15,    18,    16,    14,    13,
      12,     0,     0,     0,    11,    11,    64,    44,    45,     0,
       0,    19,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,   -35,    84,  -122,  -121,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,   -53,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     5,    76,    77,   107,   140,   145,   144,    45,
      72,    70,    46,    79,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      85,    86,    87,    88,    89,     2,    47,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    81,    82,    83,    84,
     103,   104,   105,   149,   150,    90,    91,   135,   136,   151,
     137,    48,   138,   139,     3,   101,     4,   102,    49,    71,
       3,    50,     4,   135,   136,    51,   137,   152,   138,   139,
     135,   136,    52,   137,    53,   138,   139,    54,    55,    56,
      57,   142,   143,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   130,    38,    58,    39,    40,
      41,    42,    43,    44,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    59,    38,   131,    39,
      40,    41,    42,    43,    44,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    60,    38,    61,
      39,    40,    41,    42,    43,    44,    62,    63,    64,    65,
      66,    67,    68,   141,    69,    73,    74,    75,     0,    78,
     106,   108,     0,   109,   110,   111,   112,   113,   114,   115,
     146,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   132,   133,   134,   147,
     148
};

static const yytype_int16 yycheck[] =
{
      53,    54,    55,    56,    57,     0,    34,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    49,    50,    51,    52,
      73,    74,    75,   144,   145,    58,    59,    33,    34,    35,
      36,    34,    38,    39,    35,    70,    37,    72,    34,    37,
      35,    34,    37,    33,    34,    34,    36,    37,    38,    39,
      33,    34,    34,    36,    34,    38,    39,    34,    34,    34,
      34,   114,   115,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    34,    38,    39,
      40,    41,    42,    43,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    34,    36,    37,    38,
      39,    40,    41,    42,    43,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    34,    36,    34,
      38,    39,    40,    41,    42,    43,    34,    34,    34,    34,
      34,    34,    34,   109,    35,    34,    34,    34,    -1,    39,
      35,    35,    -1,    36,    35,    35,    35,    35,    33,    33,
      37,    -1,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,     0,    35,    37,    46,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    36,    38,
      39,    40,    41,    42,    43,    53,    56,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    35,
      55,    37,    54,    34,    34,    34,    47,    48,    39,    57,
      58,    58,    58,    58,    58,    57,    57,    57,    57,    57,
      58,    58,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    46,    46,    57,    57,    57,    35,    49,    35,    36,
      35,    35,    35,    35,    33,    33,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    37,    35,    35,    35,    33,    34,    36,    38,    39,
      50,    47,    57,    57,    52,    51,    37,    35,    35,    49,
      49,    35,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    46,    46,    46,    48,
      47,    49,    49,    50,    50,    50,    51,    50,    52,    50,
      53,    53,    53,    53,    54,    53,    53,    55,    53,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     2,     1,     1,     0,
       2,     0,     2,     1,     1,     1,     0,     4,     0,     4,
       1,     1,     1,     2,     0,     4,     2,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     4,     4,     6,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     1,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 7: /* c_code: TOK_RPAREN  */
#line 384 "../../../../src/xspice/cmpp/mod_yacc.y"
                                      {yyerror ("Unmatched )"); YYERROR;}
#line 1551 "mod_yacc.c"
    break;

  case 8: /* c_code: TOK_RBRACKET  */
#line 385 "../../../../src/xspice/cmpp/mod_yacc.y"
                                       {yyerror ("Unmatched ]"); YYERROR;}
#line 1557 "mod_yacc.c"
    break;

  case 9: /* $@1: %empty  */
#line 388 "../../../../src/xspice/cmpp/mod_yacc.y"
                          {init_buffer();}
#line 1563 "mod_yacc.c"
    break;

  case 10: /* buffered_c_code: $@1 buffered_c_code2  */
#line 389 "../../../../src/xspice/cmpp/mod_yacc.y"
                          {(yyval.str) = strdup (buffer);}
#line 1569 "mod_yacc.c"
    break;

  case 13: /* buffered_c_char: TOK_IDENTIFIER  */
#line 396 "../../../../src/xspice/cmpp/mod_yacc.y"
                                         {append (mod_yytext);}
#line 1575 "mod_yacc.c"
    break;

  case 14: /* buffered_c_char: TOK_MISC_C  */
#line 397 "../../../../src/xspice/cmpp/mod_yacc.y"
                                     {append (mod_yytext);}
#line 1581 "mod_yacc.c"
    break;

  case 15: /* buffered_c_char: TOK_COMMA  */
#line 398 "../../../../src/xspice/cmpp/mod_yacc.y"
                                    {append (mod_yytext);}
#line 1587 "mod_yacc.c"
    break;

  case 16: /* $@2: %empty  */
#line 400 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {append("[");}
#line 1593 "mod_yacc.c"
    break;

  case 17: /* buffered_c_char: TOK_LBRACKET $@2 buffered_c_code2 TOK_RBRACKET  */
#line 402 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {append("]");}
#line 1599 "mod_yacc.c"
    break;

  case 18: /* $@3: %empty  */
#line 404 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {append("(");}
#line 1605 "mod_yacc.c"
    break;

  case 19: /* buffered_c_char: TOK_LPAREN $@3 buffered_c_code2 TOK_RPAREN  */
#line 406 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {append(")");}
#line 1611 "mod_yacc.c"
    break;

  case 20: /* c_char: TOK_IDENTIFIER  */
#line 409 "../../../../src/xspice/cmpp/mod_yacc.y"
                                         {fputs (mod_yytext, mod_yyout);}
#line 1617 "mod_yacc.c"
    break;

  case 21: /* c_char: TOK_MISC_C  */
#line 410 "../../../../src/xspice/cmpp/mod_yacc.y"
                                     {fputs (mod_yytext, mod_yyout);}
#line 1623 "mod_yacc.c"
    break;

  case 22: /* c_char: TOK_COMMA  */
#line 411 "../../../../src/xspice/cmpp/mod_yacc.y"
                                    {fputs (mod_yytext, mod_yyout);}
#line 1629 "mod_yacc.c"
    break;

  case 23: /* c_char: TOK_LBRACKET TOK_RBRACKET  */
#line 412 "../../../../src/xspice/cmpp/mod_yacc.y"
                                                    {fputs ("[]", mod_yyout);}
#line 1635 "mod_yacc.c"
    break;

  case 24: /* $@4: %empty  */
#line 414 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {putc ('[', mod_yyout);}
#line 1641 "mod_yacc.c"
    break;

  case 25: /* c_char: TOK_LBRACKET $@4 c_code TOK_RBRACKET  */
#line 416 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {putc (']', mod_yyout);}
#line 1647 "mod_yacc.c"
    break;

  case 26: /* c_char: TOK_LPAREN TOK_RPAREN  */
#line 417 "../../../../src/xspice/cmpp/mod_yacc.y"
                                                {fputs ("()", mod_yyout);}
#line 1653 "mod_yacc.c"
    break;

  case 27: /* $@5: %empty  */
#line 419 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {putc ('(', mod_yyout);}
#line 1659 "mod_yacc.c"
    break;

  case 28: /* c_char: TOK_LPAREN $@5 c_code TOK_RPAREN  */
#line 421 "../../../../src/xspice/cmpp/mod_yacc.y"
                                {putc (')', mod_yyout);}
#line 1665 "mod_yacc.c"
    break;

  case 29: /* macro: TOK_INIT  */
#line 425 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.init");}
#line 1671 "mod_yacc.c"
    break;

  case 30: /* macro: TOK_CALLBACK  */
#line 427 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "*(mif_private->callback)");}
#line 1677 "mod_yacc.c"
    break;

  case 31: /* macro: TOK_ARGS  */
#line 429 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "Mif_Private_t *mif_private");}
#line 1683 "mod_yacc.c"
    break;

  case 32: /* macro: TOK_ANALYSIS  */
#line 431 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.anal_type");}
#line 1689 "mod_yacc.c"
    break;

  case 33: /* macro: TOK_NEW_TIMEPOINT  */
#line 433 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.anal_init");}
#line 1695 "mod_yacc.c"
    break;

  case 34: /* macro: TOK_CALL_TYPE  */
#line 435 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.call_type");}
#line 1701 "mod_yacc.c"
    break;

  case 35: /* macro: TOK_TIME  */
#line 437 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.time");}
#line 1707 "mod_yacc.c"
    break;

  case 36: /* macro: TOK_RAD_FREQ  */
#line 439 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.frequency");}
#line 1713 "mod_yacc.c"
    break;

  case 37: /* macro: TOK_TEMPERATURE  */
#line 441 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.temperature");}
#line 1719 "mod_yacc.c"
    break;

  case 38: /* macro: TOK_T TOK_LPAREN buffered_c_code TOK_RPAREN  */
#line 443 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {fprintf (mod_yyout, "mif_private->circuit.t[%s]", (yyvsp[-1].str));}
#line 1725 "mod_yacc.c"
    break;

  case 39: /* macro: TOK_PARAM TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 445 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), PARAM);
			    fprintf (mod_yyout, "mif_private->param[%d]->element[%s]",
				     i, subscript ((yyvsp[-1].sub_id)));
			    put_type (mod_yyout, mod_ifs_table->param[i].type);
			   }
#line 1735 "mod_yacc.c"
    break;

  case 40: /* macro: TOK_PARAM_SIZE TOK_LPAREN id TOK_RPAREN  */
#line 451 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_id ((yyvsp[-1].sub_id), PARAM);
			    fprintf (mod_yyout, "mif_private->param[%d]->size", i);}
#line 1742 "mod_yacc.c"
    break;

  case 41: /* macro: TOK_PARAM_NULL TOK_LPAREN id TOK_RPAREN  */
#line 454 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_id ((yyvsp[-1].sub_id), PARAM);
			    fprintf (mod_yyout, "mif_private->param[%d]->is_null", i);}
#line 1749 "mod_yacc.c"
    break;

  case 42: /* macro: TOK_PORT_SIZE TOK_LPAREN id TOK_RPAREN  */
#line 457 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_id ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, "mif_private->conn[%d]->size", i);}
#line 1756 "mod_yacc.c"
    break;

  case 43: /* macro: TOK_PORT_NULL TOK_LPAREN id TOK_RPAREN  */
#line 460 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_id ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, "mif_private->conn[%d]->is_null", i);}
#line 1763 "mod_yacc.c"
    break;

  case 44: /* macro: TOK_PARTIAL TOK_LPAREN subscriptable_id TOK_COMMA subscriptable_id TOK_RPAREN  */
#line 464 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-3].sub_id), CONN);
			    int j = valid_subid ((yyvsp[-1].sub_id), CONN);
			    check_dir (i, CMPP_OUT, "PARTIAL");
			    check_dir (j, CMPP_IN, "PARTIAL");
			    fprintf (mod_yyout, "mif_private->conn[%d]->port[%s]->partial[%d].port[%s]",
				     i, subscript((yyvsp[-3].sub_id)), j, subscript((yyvsp[-1].sub_id)));}
#line 1774 "mod_yacc.c"
    break;

  case 45: /* macro: TOK_AC_GAIN TOK_LPAREN subscriptable_id TOK_COMMA subscriptable_id TOK_RPAREN  */
#line 472 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-3].sub_id), CONN);
			    int j = valid_subid ((yyvsp[-1].sub_id), CONN);
			    check_dir (i, CMPP_OUT, "AC_GAIN");
			    check_dir (j, CMPP_IN, "AC_GAIN");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->ac_gain[%d].port[%s]",
				     i, subscript((yyvsp[-3].sub_id)), j, subscript((yyvsp[-1].sub_id)));}
#line 1786 "mod_yacc.c"
    break;

  case 46: /* macro: TOK_STATIC_VAR TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 480 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), STATIC_VAR);
			    fprintf (mod_yyout, 
				    "mif_private->inst_var[%d]->element[%s]",
				     i, subscript((yyvsp[-1].sub_id)));
			    if (mod_ifs_table->inst_var[i].is_array
				&& !((yyvsp[-1].sub_id).has_subscript)) {
			       /* null - eg. for malloc lvalue */
			    } else {
			       put_type (mod_yyout, 
					mod_ifs_table->inst_var[i].type);
			    } }
#line 1802 "mod_yacc.c"
    break;

  case 47: /* macro: TOK_STATIC_VAR_SIZE TOK_LPAREN id TOK_RPAREN  */
#line 492 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), STATIC_VAR);
			    fprintf (mod_yyout, "mif_private->inst_var[%d]->size",
				    i);}
#line 1810 "mod_yacc.c"
    break;

  case 48: /* macro: TOK_STATIC_VAR_INST TOK_LPAREN id TOK_RPAREN  */
#line 496 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), STATIC_VAR);
			    fprintf (mod_yyout, "mif_private->inst_var[%d]",
				    i);}
#line 1818 "mod_yacc.c"
    break;

  case 49: /* macro: TOK_OUTPUT_DELAY TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 500 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    check_dir (i, CMPP_OUT, "OUTPUT_DELAY");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->delay", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1828 "mod_yacc.c"
    break;

  case 50: /* macro: TOK_CHANGED TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 506 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    check_dir (i, CMPP_OUT, "CHANGED");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->changed", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1838 "mod_yacc.c"
    break;

  case 51: /* macro: TOK_INPUT TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 512 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_IN, "INPUT");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->input",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);}
#line 1850 "mod_yacc.c"
    break;

  case 52: /* macro: TOK_INPUT_TYPE TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 520 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_IN, "INPUT_TYPE");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->type_str",
				     i, subscript((yyvsp[-1].sub_id))); }
#line 1860 "mod_yacc.c"
    break;

  case 53: /* macro: TOK_OUTPUT_TYPE TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 526 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_OUT, "OUTPUT_TYPE");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->type_str",
				     i, subscript((yyvsp[-1].sub_id))); }
#line 1870 "mod_yacc.c"
    break;

  case 54: /* macro: TOK_INPUT_STRENGTH TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 532 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_IN, "INPUT_STRENGTH");
			    fprintf (mod_yyout, 
				     "((Digital_t*)(mif_private->conn[%d]->port[%s]->input",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);
			    fprintf (mod_yyout, "))->strength");}
#line 1883 "mod_yacc.c"
    break;

  case 55: /* macro: TOK_INPUT_STATE TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 541 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_IN, "INPUT_STATE");
			    fprintf (mod_yyout, 
				     "((Digital_t*)(mif_private->conn[%d]->port[%s]->input",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);
			    fprintf (mod_yyout, "))->state");}
#line 1896 "mod_yacc.c"
    break;

  case 56: /* macro: TOK_OUTPUT TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 550 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_OUT, "OUTPUT");
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->output",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);}
#line 1908 "mod_yacc.c"
    break;

  case 57: /* macro: TOK_OUTPUT_STRENGTH TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 558 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_OUT, "OUTPUT_STRENGTH");
			    fprintf (mod_yyout, 
				     "((Digital_t*)(mif_private->conn[%d]->port[%s]->output",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);
			    fprintf (mod_yyout, "))->strength");}
#line 1921 "mod_yacc.c"
    break;

  case 58: /* macro: TOK_OUTPUT_STATE TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 567 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
 			    check_dir (i, CMPP_OUT, "OUTPUT_STATE");
			    fprintf (mod_yyout, 
				     "((Digital_t*)(mif_private->conn[%d]->port[%s]->output",
				     i, subscript((yyvsp[-1].sub_id)));
			    put_conn_type (mod_yyout, 
			       mod_ifs_table->conn[i].allowed_port_type[0]);
			    fprintf (mod_yyout, "))->state");}
#line 1934 "mod_yacc.c"
    break;

  case 59: /* macro: TOK_OUTPUT_CHANGED TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 576 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->changed", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1943 "mod_yacc.c"
    break;

  case 60: /* macro: TOK_LOAD TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 581 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->load", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1952 "mod_yacc.c"
    break;

  case 61: /* macro: TOK_TOTAL_LOAD TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 586 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->total_load", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1961 "mod_yacc.c"
    break;

  case 62: /* macro: TOK_MESSAGE TOK_LPAREN subscriptable_id TOK_RPAREN  */
#line 591 "../../../../src/xspice/cmpp/mod_yacc.y"
                           {int i = valid_subid ((yyvsp[-1].sub_id), CONN);
			    fprintf (mod_yyout, 
				     "mif_private->conn[%d]->port[%s]->msg", i,
				     subscript((yyvsp[-1].sub_id)));}
#line 1970 "mod_yacc.c"
    break;

  case 64: /* subscriptable_id: id TOK_LBRACKET buffered_c_code TOK_RBRACKET  */
#line 599 "../../../../src/xspice/cmpp/mod_yacc.y"
                          {(yyval.sub_id) = (yyvsp[-3].sub_id);
			   (yyval.sub_id).has_subscript = true;
			   (yyval.sub_id).subscript = (yyvsp[-1].str);}
#line 1978 "mod_yacc.c"
    break;

  case 65: /* id: TOK_IDENTIFIER  */
#line 605 "../../../../src/xspice/cmpp/mod_yacc.y"
                             {(yyval.sub_id).has_subscript = false;
			      (yyval.sub_id).id = strdup (mod_yytext);}
#line 1985 "mod_yacc.c"
    break;


#line 1989 "mod_yacc.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 609 "../../../../src/xspice/cmpp/mod_yacc.y"

