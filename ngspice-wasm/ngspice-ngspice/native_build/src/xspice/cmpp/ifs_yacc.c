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
#line 1 "../../../../src/xspice/cmpp/ifs_yacc.y"


/*============================================================================
FILE  ifs_yacc.y

MEMBER OF process cmpp

Copyright 1991
Georgia Tech Research Corporation
Atlanta, Georgia 30332
All Rights Reserved

PROJECT A-8503

AUTHORS

    9/12/91  Steve Tynor

MODIFICATIONS

    12/31/91  Bill Kuhn  Fix bug in usage of strcmp in check_default_type()

SUMMARY

    This file contains the BNF specification of the language used in
    the ifspec.ifs file together with various support functions,
    and parses the ifspec.ifs file to get the information from it
    and place this information into a data structure
    of type Ifs_Table_t.

INTERFACES

    yyparse()     -    Generated automatically by UNIX 'yacc' utility.

REFERENCED FILES

    ifs_lex.l

NON-STANDARD FEATURES

    None.

============================================================================*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ifs_yacc_y.h"

#define yymaxdepth ifs_yymaxdepth
#define yyparse ifs_yyparse
#define yylex   ifs_yylex
#define yyerror ifs_yyerror
#define yylval  ifs_yylval
#define yychar  ifs_yychar
#define yydebug ifs_yydebug
#define yypact  ifs_yypact
#define yyr1    ifs_yyr1
#define yyr2    ifs_yyr2
#define yydef   ifs_yydef
#define yychk   ifs_yychk
#define yypgo   ifs_yypgo
#define yyact   ifs_yyact
#define yyexca  ifs_yyexca
#define yyerrflag ifs_yyerrflag
#define yynerrs ifs_yynerrs
#define yyps    ifs_yyps
#define yypv    ifs_yypv
#define yys ifs_yys
#define yy_yys  ifs_yyyys
#define yystate ifs_yystate
#define yytmp   ifs_yytmp
#define yyv ifs_yyv
#define yy_yyv  ifs_yyyyv
#define yyval   ifs_yyval
#define yylloc  ifs_yylloc
#define yyreds  ifs_yyreds
#define yytoks  ifs_yytoks
#define yylhs   ifs_yyyylhs
#define yylen   ifs_yyyylen
#define yydefred ifs_yyyydefred
#define yydgoto ifs_yyyydgoto
#define yysindex ifs_yyyysindex
#define yyrindex ifs_yyyyrindex
#define yygindex ifs_yyyygindex
#define yytable  ifs_yyyytable
#define yycheck  ifs_yyyycheck
#define yyname   ifs_yyyyname
#define yyrule   ifs_yyyyrule

extern int yylineno;
extern int yyival;
extern double yydval;
extern char *ifs_yytext;
 extern int ifs_yylex(void);

bool parser_just_names;
static bool saw_model_name;
static bool saw_function_name;

static char *dtype_to_str[] = {
   "BOOLEAN", "INTEGER", "REAL", "COMPLEX", "STRING", "POINTER"
   };

static bool did_default_type;
static bool did_allowed_types;

static int num_items;
static int item;
static int item_offset;
static bool num_items_fixed;

Ifs_Table_t *parser_ifs_table;
#define TBL parser_ifs_table

int ifs_num_errors;

/* Allocated and initial sizes of tables for parse results. */

static size_t alloced_size [5];

#define DEFAULT_SIZE_CONN   10
#define DEFAULT_SIZE_PARAM  10
#define DEFAULT_SIZE_INST_VAR   10
#define DEFAULT_SIZE_DEFAULTS   100
#define GROW_SIZE       10

typedef enum {
   TBL_NAME,
   TBL_PORT,
   TBL_PARAMETER,
   TBL_STATIC_VAR,
   TBL_DEFAULTS,
} Table_t;

typedef struct {
   Table_t table;
   int record;
} Context_t;

Context_t context;

#define ITEM_BUFFER_SIZE 20 /* number of items that can be put in a table
                 * before requiring a new xxx_TABLE: keyword
                 */
#define FOR_ITEM(i) for (i = item_offset; i < num_items; i++)
#define ITEM_BUF(i) item_buffer[i-item_offset]

#define ASSIGN_BOUNDS(struct_name, i) \
  if (ITEM_BUF(i).range.is_named) {\
    TBL->struct_name[i].has_conn_ref = true;\
    TBL->struct_name[i].conn_ref = find_conn_ref (ITEM_BUF(i).range.u.name);\
  } else {\
    TBL->struct_name[i].has_conn_ref = false;\
    TBL->struct_name[i].has_lower_bound =\
       ITEM_BUF(i).range.u.bounds.lower.has_bound;\
    TBL->struct_name[i].has_upper_bound =\
       ITEM_BUF(i).range.u.bounds.upper.has_bound;\
    if (TBL->struct_name[i].has_lower_bound) {\
      assert (ITEM_BUF(i).range.u.bounds.lower.bound.kind == CMPP_INTEGER);\
       TBL->struct_name[i].lower_bound =\
    ITEM_BUF(i).range.u.bounds.lower.bound.u.ivalue;\
    }\
    if (TBL->struct_name[i].has_upper_bound) {\
       assert (ITEM_BUF(i).range.u.bounds.upper.bound.kind == CMPP_INTEGER);\
       TBL->struct_name[i].upper_bound =\
      ITEM_BUF(i).range.u.bounds.upper.bound.u.ivalue;\
    }\
  }

/*---------------------------------------------------------------------------*/
static void fatal (char *str)
{
   yyerror (str);
   exit(1);
}

/*---------------------------------------------------------------------------*/
static int
find_conn_ref (char *name)
{
   int i;
   char str[130];
   
   for (i = 0; i < TBL->num_conn; i++) {
      if (strcmp (name, TBL->conn[i].name) == 0) {
     return i;
      }
   }
   sprintf (str, "Port `%s' not found", name);
   yyerror (str);
   ifs_num_errors++;

   return 0;
}

typedef enum {C_DOUBLE, C_BOOLEAN, C_POINTER, C_UNDEF} Ctype_Class_t;

/*---------------------------------------------------------------------------*/
static Ctype_Class_t get_ctype_class (Port_Type_t type)
{
   switch (type) {
   case USER_DEFINED:
      return C_POINTER;
      break;
   case DIGITAL:
      return C_BOOLEAN;
      break;
   default:
      return C_DOUBLE;
      break;
   }
}

/*---------------------------------------------------------------------------*/
static void check_port_type_direction (Dir_t dir, Port_Type_t port_type)
{
   switch (port_type) {
   case VOLTAGE:
   case DIFF_VOLTAGE:
   case CURRENT:
   case DIFF_CURRENT:
      if (dir == CMPP_INOUT) {
         yyerror ("Port types `v', `vd', `i', `id' are not valid for `inout' ports");
         ifs_num_errors++;
      }
       break;
   case DIGITAL:
   case USER_DEFINED:
      /*
       * anything goes
       */
      break;
   case VSOURCE_CURRENT:
      if (dir != CMPP_IN) {
         yyerror ("Port type `vnam' is only valid for `in' ports");
         ifs_num_errors++;
      }
      break;
   case CONDUCTANCE:
   case DIFF_CONDUCTANCE:
   case RESISTANCE:
   case DIFF_RESISTANCE:
      if (dir != CMPP_INOUT) {
         yyerror ("Port types `g', `gd', `h', `hd' are only valid for `inout' ports");
         ifs_num_errors++;
      }
      break;
   default:
      assert (0);
   }
}

/*---------------------------------------------------------------------------*/
static void check_dtype_not_pointer (Data_Type_t dtype)
{
   if (dtype == CMPP_POINTER) {
      yyerror("Invalid parameter type - POINTER type valid only for STATIC_VARs");
      ifs_num_errors++;
   }
}

/*---------------------------------------------------------------------------*/
static void check_default_type (Conn_Info_t conn)
{
   int i;
   
   for (i = 0; i < conn.num_allowed_types; i++) {
      if (conn.default_port_type == conn.allowed_port_type[i]) {
         if ((conn.default_port_type != USER_DEFINED) ||
            (strcmp (conn.default_type, conn.allowed_type[i]) == 0)) {
         return;
         }
      }
   }
   yyerror ("Port default type is not an allowed type");
   ifs_num_errors++;
}

/*---------------------------------------------------------------------------*/
static void
assign_ctype_list (Conn_Info_t  *conn, Ctype_List_t *ctype_list )
{
   int i;
   Ctype_List_t *p;
   Ctype_Class_t ctype_class = C_UNDEF;
   
   conn->num_allowed_types = 0;
   for (p = ctype_list; p; p = p->next) {
      conn->num_allowed_types++;
   }
   conn->allowed_type = (char**) calloc ((size_t) conn->num_allowed_types,
                     sizeof (char*));
   conn->allowed_port_type = (Port_Type_t*) calloc ((size_t) conn->num_allowed_types,
                            sizeof (Port_Type_t));
   if (! (conn->allowed_type && conn->allowed_port_type)) {
      fatal ("Could not allocate memory");
   }
   for (i = conn->num_allowed_types-1, p = ctype_list; p; i--, p = p->next) {
      if (ctype_class == C_UNDEF) {
         ctype_class = get_ctype_class (p->ctype.kind);
      }
      if (ctype_class != get_ctype_class (p->ctype.kind)) {
        yyerror ("Incompatible port types in `allowed_types' clause");
        ifs_num_errors++;
      }
      check_port_type_direction (conn->direction, p->ctype.kind);
      
      conn->allowed_port_type[i] = p->ctype.kind;
      conn->allowed_type[i] = p->ctype.id;
   } 
}

/*---------------------------------------------------------------------------*/
static void
assign_value (Data_Type_t type, Value_t *dest_value, My_Value_t src_value)
{
   char str[200];
   if ((type == CMPP_REAL) && (src_value.kind == CMPP_INTEGER)) {
      dest_value->rvalue = src_value.u.ivalue;
      return;
   } else if (type != src_value.kind) {
      sprintf (str, "Invalid parameter type (saw %s - expected %s)",
           dtype_to_str[src_value.kind],
           dtype_to_str[type] );
      yyerror (str);
      ifs_num_errors++;
   } 
   switch (type) {
   case CMPP_BOOLEAN:
      dest_value->bvalue = src_value.u.bvalue;
      break;
   case CMPP_INTEGER:
      dest_value->ivalue = src_value.u.ivalue;
      break;
   case CMPP_REAL:
      dest_value->rvalue = src_value.u.rvalue;
      break;
   case CMPP_COMPLEX:
      dest_value->cvalue = src_value.u.cvalue;
      break;
   case CMPP_STRING:
      dest_value->svalue = src_value.u.svalue;
      break;
   default:
      yyerror ("INTERNAL ERROR - unexpected data type in `assign_value'");
      ifs_num_errors++;
   }
}   

/*---------------------------------------------------------------------------*/
static void
assign_limits (Data_Type_t type, Param_Info_t *param, Range_t range)
{
   if (range.is_named) {
      yyerror ("Named range not allowed for limits");
      ifs_num_errors++;
   }
   param->has_lower_limit = range.u.bounds.lower.has_bound;
   if (param->has_lower_limit) {
      assign_value (type, &param->lower_limit, range.u.bounds.lower.bound);
   }
   param->has_upper_limit = range.u.bounds.upper.has_bound;
   if (param->has_upper_limit) {
      assign_value (type, &param->upper_limit, range.u.bounds.upper.bound);
   }
}

/*---------------------------------------------------------------------------*/
/* Advance the item variable, checking for table overflow. */

static void
check_item_num (void)
{
   item++;
   if (item-item_offset >= ITEM_BUFFER_SIZE) {
      fatal("Too many items in table - split into sub-tables");
   }
   if (item >= (int) alloced_size [context.table] ) {
      switch (context.table) {
      case TBL_NAME:     // Fixed size.
      case TBL_DEFAULTS: // Handled in store_default_value().
         break;
      case TBL_PORT:
         alloced_size[context.table] += GROW_SIZE;
         TBL->conn = (Conn_Info_t*)
               realloc (TBL->conn,
               alloced_size [context.table] * sizeof (Conn_Info_t));
         if (! TBL->conn) {
            fatal ("Error allocating memory for port definition");
         }
         break;
      case TBL_PARAMETER:
         alloced_size [context.table] += GROW_SIZE;
         TBL->param = (Param_Info_t*)
               realloc (TBL->param,
               alloced_size [context.table] * sizeof (Param_Info_t));
         if (! TBL->param) {
            fatal ("Error allocating memory for parameter definition");
         }
         break;
      case TBL_STATIC_VAR:
         alloced_size [context.table] += GROW_SIZE;
         TBL->inst_var = (Inst_Var_Info_t*)
               realloc (TBL->inst_var,
               alloced_size [context.table] * sizeof (Inst_Var_Info_t));
        if (! TBL->inst_var) {
           fatal ("Error allocating memory for static variable definition");
        }
        break;
      }
   }
}

/*---------------------------------------------------------------------------*/
static void
check_end_item_num (void)
{
   if (num_items_fixed) {
      if (item != num_items) {
         char buf[200];
         sprintf
               (buf,
               "Wrong number of elements in sub-table (saw %d - expected %d)",
               item - item_offset,
               num_items - item_offset);
         fatal (buf);
      }
   } else {
      num_items = item;
      num_items_fixed = true;
      switch (context.table) {
      case TBL_NAME:
      case TBL_DEFAULTS:
         break;
      case TBL_PORT:
         TBL->num_conn = num_items;
         break;
      case TBL_PARAMETER:
         TBL->num_param = num_items;
         break;
      case TBL_STATIC_VAR:
         TBL->num_inst_var = num_items;
         break;
      }
   }
   item = item_offset;
}

#define INIT(n) item = (n); item_offset = (n); num_items = (n); num_items_fixed = false
#define ITEM check_item_num()     // Advances the item_buffer index.
#define END  check_end_item_num() // Check for excessive values in later row.
   
/* Store a default value for a parameter. */

static void store_default_value(My_Value_t *vp)
{
    if (TBL->num_default_values >= alloced_size[TBL_DEFAULTS]) {
        /* Expand table. */

        alloced_size [TBL_DEFAULTS] += GROW_SIZE * 5;
        TBL->defaults_var = (My_Value_t *) realloc(TBL->defaults_var,
               alloced_size[TBL_DEFAULTS] * sizeof (My_Value_t));
        if (!TBL->defaults_var) {
           fatal ("Error allocating memory for default parameter values");
        }
    }
    TBL->defaults_var[TBL->num_default_values++] = *vp;
    if (vp->advance)
        ITEM;   // Count another parameter sub-table.
}


#line 545 "ifs_yacc.c"

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

#include "ifs_yacc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_ALLOWED_TYPES = 3,          /* TOK_ALLOWED_TYPES  */
  YYSYMBOL_TOK_ARRAY = 4,                  /* TOK_ARRAY  */
  YYSYMBOL_TOK_ARRAY_BOUNDS = 5,           /* TOK_ARRAY_BOUNDS  */
  YYSYMBOL_TOK_BOOL_NO = 6,                /* TOK_BOOL_NO  */
  YYSYMBOL_TOK_BOOL_YES = 7,               /* TOK_BOOL_YES  */
  YYSYMBOL_TOK_COMMA = 8,                  /* TOK_COMMA  */
  YYSYMBOL_TOK_PORT_NAME = 9,              /* TOK_PORT_NAME  */
  YYSYMBOL_TOK_PORT_TABLE = 10,            /* TOK_PORT_TABLE  */
  YYSYMBOL_TOK_CTYPE_D = 11,               /* TOK_CTYPE_D  */
  YYSYMBOL_TOK_CTYPE_G = 12,               /* TOK_CTYPE_G  */
  YYSYMBOL_TOK_CTYPE_GD = 13,              /* TOK_CTYPE_GD  */
  YYSYMBOL_TOK_CTYPE_H = 14,               /* TOK_CTYPE_H  */
  YYSYMBOL_TOK_CTYPE_HD = 15,              /* TOK_CTYPE_HD  */
  YYSYMBOL_TOK_CTYPE_I = 16,               /* TOK_CTYPE_I  */
  YYSYMBOL_TOK_CTYPE_ID = 17,              /* TOK_CTYPE_ID  */
  YYSYMBOL_TOK_CTYPE_V = 18,               /* TOK_CTYPE_V  */
  YYSYMBOL_TOK_CTYPE_VD = 19,              /* TOK_CTYPE_VD  */
  YYSYMBOL_TOK_CTYPE_VNAM = 20,            /* TOK_CTYPE_VNAM  */
  YYSYMBOL_TOK_C_FUNCTION_NAME = 21,       /* TOK_C_FUNCTION_NAME  */
  YYSYMBOL_TOK_DASH = 22,                  /* TOK_DASH  */
  YYSYMBOL_TOK_DATA_TYPE = 23,             /* TOK_DATA_TYPE  */
  YYSYMBOL_TOK_DEFAULT_TYPE = 24,          /* TOK_DEFAULT_TYPE  */
  YYSYMBOL_TOK_DEFAULT_VALUE = 25,         /* TOK_DEFAULT_VALUE  */
  YYSYMBOL_TOK_DESCRIPTION = 26,           /* TOK_DESCRIPTION  */
  YYSYMBOL_TOK_DIRECTION = 27,             /* TOK_DIRECTION  */
  YYSYMBOL_TOK_DIR_IN = 28,                /* TOK_DIR_IN  */
  YYSYMBOL_TOK_DIR_INOUT = 29,             /* TOK_DIR_INOUT  */
  YYSYMBOL_TOK_DIR_OUT = 30,               /* TOK_DIR_OUT  */
  YYSYMBOL_TOK_DTYPE_BOOLEAN = 31,         /* TOK_DTYPE_BOOLEAN  */
  YYSYMBOL_TOK_DTYPE_COMPLEX = 32,         /* TOK_DTYPE_COMPLEX  */
  YYSYMBOL_TOK_DTYPE_INT = 33,             /* TOK_DTYPE_INT  */
  YYSYMBOL_TOK_DTYPE_POINTER = 34,         /* TOK_DTYPE_POINTER  */
  YYSYMBOL_TOK_DTYPE_REAL = 35,            /* TOK_DTYPE_REAL  */
  YYSYMBOL_TOK_DTYPE_STRING = 36,          /* TOK_DTYPE_STRING  */
  YYSYMBOL_TOK_IDENTIFIER = 37,            /* TOK_IDENTIFIER  */
  YYSYMBOL_TOK_STATIC_VAR_NAME = 38,       /* TOK_STATIC_VAR_NAME  */
  YYSYMBOL_TOK_STATIC_VAR_TABLE = 39,      /* TOK_STATIC_VAR_TABLE  */
  YYSYMBOL_TOK_INT_LITERAL = 40,           /* TOK_INT_LITERAL  */
  YYSYMBOL_TOK_LANGLE = 41,                /* TOK_LANGLE  */
  YYSYMBOL_TOK_LBRACKET = 42,              /* TOK_LBRACKET  */
  YYSYMBOL_TOK_LIMITS = 43,                /* TOK_LIMITS  */
  YYSYMBOL_TOK_NAME_TABLE = 44,            /* TOK_NAME_TABLE  */
  YYSYMBOL_TOK_NULL_ALLOWED = 45,          /* TOK_NULL_ALLOWED  */
  YYSYMBOL_TOK_PARAMETER_NAME = 46,        /* TOK_PARAMETER_NAME  */
  YYSYMBOL_TOK_PARAMETER_TABLE = 47,       /* TOK_PARAMETER_TABLE  */
  YYSYMBOL_TOK_RANGLE = 48,                /* TOK_RANGLE  */
  YYSYMBOL_TOK_RBRACKET = 49,              /* TOK_RBRACKET  */
  YYSYMBOL_TOK_REAL_LITERAL = 50,          /* TOK_REAL_LITERAL  */
  YYSYMBOL_TOK_SPICE_MODEL_NAME = 51,      /* TOK_SPICE_MODEL_NAME  */
  YYSYMBOL_TOK_STRING_LITERAL = 52,        /* TOK_STRING_LITERAL  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_ifs_file = 54,                  /* ifs_file  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_list_of_tables = 56,            /* list_of_tables  */
  YYSYMBOL_table = 57,                     /* table  */
  YYSYMBOL_58_2 = 58,                      /* $@2  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_60_4 = 60,                      /* $@4  */
  YYSYMBOL_61_5 = 61,                      /* $@5  */
  YYSYMBOL_name_table = 62,                /* name_table  */
  YYSYMBOL_name_table_item = 63,           /* name_table_item  */
  YYSYMBOL_port_table = 64,                /* port_table  */
  YYSYMBOL_port_table_item = 65,           /* port_table_item  */
  YYSYMBOL_parameter_table = 66,           /* parameter_table  */
  YYSYMBOL_parameter_table_item = 67,      /* parameter_table_item  */
  YYSYMBOL_static_var_table = 68,          /* static_var_table  */
  YYSYMBOL_static_var_table_item = 69,     /* static_var_table_item  */
  YYSYMBOL_list_of_ids = 70,               /* list_of_ids  */
  YYSYMBOL_list_of_array_bounds = 71,      /* list_of_array_bounds  */
  YYSYMBOL_list_of_strings = 72,           /* list_of_strings  */
  YYSYMBOL_list_of_directions = 73,        /* list_of_directions  */
  YYSYMBOL_direction = 74,                 /* direction  */
  YYSYMBOL_list_of_bool = 75,              /* list_of_bool  */
  YYSYMBOL_list_of_ctypes = 76,            /* list_of_ctypes  */
  YYSYMBOL_ctype = 77,                     /* ctype  */
  YYSYMBOL_list_of_dtypes = 78,            /* list_of_dtypes  */
  YYSYMBOL_dtype = 79,                     /* dtype  */
  YYSYMBOL_list_of_ranges = 80,            /* list_of_ranges  */
  YYSYMBOL_int_range = 81,                 /* int_range  */
  YYSYMBOL_maybe_comma = 82,               /* maybe_comma  */
  YYSYMBOL_int_or_dash = 83,               /* int_or_dash  */
  YYSYMBOL_range = 84,                     /* range  */
  YYSYMBOL_number_or_dash = 85,            /* number_or_dash  */
  YYSYMBOL_list_of_pure_values = 86,       /* list_of_pure_values  */
  YYSYMBOL_list_of_default_values = 87,    /* list_of_default_values  */
  YYSYMBOL_value_or_dash = 88,             /* value_or_dash  */
  YYSYMBOL_value = 89,                     /* value  */
  YYSYMBOL_complex = 90,                   /* complex  */
  YYSYMBOL_list_of_ctype_lists = 91,       /* list_of_ctype_lists  */
  YYSYMBOL_delimited_ctype_list = 92,      /* delimited_ctype_list  */
  YYSYMBOL_ctype_list = 93,                /* ctype_list  */
  YYSYMBOL_btype = 94,                     /* btype  */
  YYSYMBOL_string = 95,                    /* string  */
  YYSYMBOL_identifier = 96,                /* identifier  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_integer_value = 98,             /* integer_value  */
  YYSYMBOL_real = 99,                      /* real  */
  YYSYMBOL_integer = 100                   /* integer  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 568 "../../../../src/xspice/cmpp/ifs_yacc.y"

/*
 * resuse the Yacc union for our buffer:
 */
YYSTYPE item_buffer [ITEM_BUFFER_SIZE];

/*
 * Shorthand for refering to the current element of the item buffer:
 */
#define BUF ITEM_BUF(item-1)


#line 692 "ifs_yacc.c"


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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   583,   583,   583,   612,   613,   617,   616,   620,   619,
     627,   626,   632,   631,   638,   639,   642,   646,   650,   654,
     655,   658,   664,   670,   676,   688,   699,   705,   712,   720,
     721,   724,   730,   736,   743,   745,   753,   759,   765,   773,
     774,   777,   783,   789,   795,   803,   804,   807,   808,   811,
     817,   818,   821,   822,   825,   826,   827,   830,   831,   834,
     835,   838,   839,   840,   841,   842,   843,   844,   845,   846,
     847,   848,   852,   853,   856,   857,   858,   859,   860,   861,
     864,   865,   868,   871,   878,   879,   882,   883,   887,   890,
     897,   898,   902,   903,   907,   908,   910,   913,   914,   917,
     920,   923,   926,   929,   934,   935,   939,   942,   950,   963,
     964,   967,   970,   973,   976,   979,   984,   987
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_ALLOWED_TYPES",
  "TOK_ARRAY", "TOK_ARRAY_BOUNDS", "TOK_BOOL_NO", "TOK_BOOL_YES",
  "TOK_COMMA", "TOK_PORT_NAME", "TOK_PORT_TABLE", "TOK_CTYPE_D",
  "TOK_CTYPE_G", "TOK_CTYPE_GD", "TOK_CTYPE_H", "TOK_CTYPE_HD",
  "TOK_CTYPE_I", "TOK_CTYPE_ID", "TOK_CTYPE_V", "TOK_CTYPE_VD",
  "TOK_CTYPE_VNAM", "TOK_C_FUNCTION_NAME", "TOK_DASH", "TOK_DATA_TYPE",
  "TOK_DEFAULT_TYPE", "TOK_DEFAULT_VALUE", "TOK_DESCRIPTION",
  "TOK_DIRECTION", "TOK_DIR_IN", "TOK_DIR_INOUT", "TOK_DIR_OUT",
  "TOK_DTYPE_BOOLEAN", "TOK_DTYPE_COMPLEX", "TOK_DTYPE_INT",
  "TOK_DTYPE_POINTER", "TOK_DTYPE_REAL", "TOK_DTYPE_STRING",
  "TOK_IDENTIFIER", "TOK_STATIC_VAR_NAME", "TOK_STATIC_VAR_TABLE",
  "TOK_INT_LITERAL", "TOK_LANGLE", "TOK_LBRACKET", "TOK_LIMITS",
  "TOK_NAME_TABLE", "TOK_NULL_ALLOWED", "TOK_PARAMETER_NAME",
  "TOK_PARAMETER_TABLE", "TOK_RANGLE", "TOK_RBRACKET", "TOK_REAL_LITERAL",
  "TOK_SPICE_MODEL_NAME", "TOK_STRING_LITERAL", "$accept", "ifs_file",
  "$@1", "list_of_tables", "table", "$@2", "$@3", "$@4", "$@5",
  "name_table", "name_table_item", "port_table", "port_table_item",
  "parameter_table", "parameter_table_item", "static_var_table",
  "static_var_table_item", "list_of_ids", "list_of_array_bounds",
  "list_of_strings", "list_of_directions", "direction", "list_of_bool",
  "list_of_ctypes", "ctype", "list_of_dtypes", "dtype", "list_of_ranges",
  "int_range", "maybe_comma", "int_or_dash", "range", "number_or_dash",
  "list_of_pure_values", "list_of_default_values", "value_or_dash",
  "value", "complex", "list_of_ctype_lists", "delimited_ctype_list",
  "ctype_list", "btype", "string", "identifier", "number", "integer_value",
  "real", "integer", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -102,    21,    39,  -102,  -102,  -102,  -102,  -102,    39,  -102,
    -102,  -102,  -102,  -102,  -102,    58,    32,    50,    64,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,     6,   -27,     6,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,   -15,    92,   -14,     6,
     106,   -27,    51,    92,    92,    96,   -27,     6,  -102,  -102,
    -102,  -102,  -102,    92,   -14,    96,     0,   -27,   -10,    92,
       6,   106,  -102,  -102,  -102,  -102,  -102,    -6,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,   -13,     7,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
      66,  -102,  -102,    11,  -102,    43,  -102,    43,     4,  -102,
    -102,    43,  -102,  -102,  -102,   106,    -6,   -13,  -102,  -102,
      66,  -102,    25,    27,    42,  -102,  -102,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     8,    12,     6,    10,     3,     4,
      19,    39,    14,    29,     5,     9,    13,     7,    11,   104,
      57,    47,    45,    59,    50,    52,    57,    20,    57,    72,
      50,    45,    40,     0,     0,     0,    15,    57,    47,    72,
      94,    50,    80,    57,    45,    30,    25,    26,    27,    21,
      24,    22,    23,    28,    44,    43,    42,    41,   112,    16,
     111,    18,    17,    36,    37,    33,    34,    32,    35,    38,
      31,     0,   105,   110,   109,    58,    82,     0,    48,    49,
      46,    70,    66,    67,    68,    69,    64,    65,    61,    62,
      63,    60,    71,    51,    54,    56,    55,    53,    76,    77,
      75,    79,    74,    78,    73,    97,   117,     0,     0,   116,
      95,    98,   101,   100,    99,   102,   114,   113,   115,    88,
       0,    81,   107,    84,    86,    84,    87,    84,     0,    92,
      90,    84,    91,    85,   106,     0,     0,     0,    96,    93,
       0,   108,     0,     0,     0,    83,   103,    89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,  -102,  -102,  -102,    87,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,   -11,    62,   -12,
    -102,  -102,    68,  -102,   -70,    65,  -102,  -102,  -102,  -101,
     -28,  -102,   -26,  -102,  -102,  -102,   -36,  -102,  -102,  -102,
    -102,   -62,   -31,   -33,   -47,   -72,   -98,  -102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    12,    10,    13,    11,    17,
      36,    15,    27,    18,    45,    16,    32,    49,    48,    51,
      52,    97,    47,    50,    91,    55,   104,    68,    78,   135,
     125,   121,   131,   128,    66,   110,   111,   112,    46,    72,
     123,    75,    93,    80,   115,   116,   117,   118
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,   122,    62,    61,   113,   126,    73,    74,    76,   127,
      73,    74,   119,    73,    74,    79,   124,    92,    56,   133,
      57,     3,   105,    58,   136,    60,   137,    71,    77,    67,
     140,    79,   120,    70,   106,   114,    28,   109,    92,   143,
     106,   107,   108,    58,   106,   107,   113,   106,   107,     4,
     109,   133,    60,   138,   109,    29,    60,   109,    30,    60,
     134,    19,    20,    21,   126,   141,   113,    22,    37,    38,
      31,    33,   129,   132,   145,   146,    34,   114,     5,    94,
      95,    96,    23,     6,    24,    25,     7,    39,   130,    40,
      41,   147,   139,   132,    53,    14,    54,   114,    73,    74,
      64,    35,    92,    26,    65,    63,   106,    42,   142,    43,
      44,    69,     0,     0,   144,     0,   109,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58
};

static const yytype_int16 yycheck[] =
{
      33,    71,    35,    34,    66,    77,     6,     7,    22,   107,
       6,     7,    22,     6,     7,    48,    22,    50,    30,     8,
      31,     0,    22,    37,   125,    52,   127,    42,    42,    41,
     131,    64,    42,    44,    40,    66,     4,    50,    71,   137,
      40,    41,    42,    37,    40,    41,   108,    40,    41,    10,
      50,     8,    52,    49,    50,    23,    52,    50,    26,    52,
      49,     3,     4,     5,   136,   135,   128,     9,     4,     5,
      38,    21,   108,   120,    49,    48,    26,   108,    39,    28,
      29,    30,    24,    44,    26,    27,    47,    23,    22,    25,
      26,    49,   128,   140,    26,     8,    28,   128,     6,     7,
      38,    51,   135,    45,    39,    37,    40,    43,   136,    45,
      46,    43,    -1,    -1,   140,    -1,    50,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,     0,    10,    39,    44,    47,    56,    57,
      59,    61,    58,    60,    57,    64,    68,    62,    66,     3,
       4,     5,     9,    24,    26,    27,    45,    65,     4,    23,
      26,    38,    69,    21,    26,    51,    63,     4,     5,    23,
      25,    26,    43,    45,    46,    67,    91,    75,    71,    70,
      76,    72,    73,    75,    75,    78,    72,    70,    37,    96,
      52,    95,    96,    75,    71,    78,    87,    72,    80,    75,
      70,    42,    92,     6,     7,    94,    22,    42,    81,    96,
      96,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    77,    96,    95,    28,    29,    30,    74,    31,    32,
      33,    34,    35,    36,    79,    22,    40,    41,    42,    50,
      88,    89,    90,    94,    95,    97,    98,    99,   100,    22,
      42,    84,    77,    93,    22,    83,    98,    99,    86,    89,
      22,    85,    97,     8,    49,    82,    82,    82,    49,    89,
      82,    77,    83,    99,    85,    49,    48,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    55,    54,    56,    56,    58,    57,    59,    57,
      60,    57,    61,    57,    62,    62,    63,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    69,    69,    70,    70,    71,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    88,    88,    89,
      89,    89,    89,    90,    91,    91,    92,    93,    93,    94,
      94,    95,    96,    97,    97,    98,    99,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     0,     2,     0,     2,     2,
       0,     2,     0,     2,     1,     1,     1,     0,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     5,     0,     1,     1,     1,     1,     5,
       1,     1,     1,     2,     0,     2,     4,     1,     1,     1,
       1,     1,     1,     5,     0,     2,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
  case 2: /* $@1: %empty  */
#line 583 "../../../../src/xspice/cmpp/ifs_yacc.y"
           {TBL->num_conn = 0;
               TBL->num_param = 0;
               TBL->num_inst_var = 0;
               TBL->num_default_values = 0;

               saw_function_name = false;
               saw_model_name = false;

               alloced_size [TBL_PORT] = DEFAULT_SIZE_CONN;
               alloced_size [TBL_PARAMETER] = DEFAULT_SIZE_PARAM;
               alloced_size [TBL_STATIC_VAR] = DEFAULT_SIZE_INST_VAR;
               alloced_size [TBL_DEFAULTS] = DEFAULT_SIZE_DEFAULTS;

               TBL->conn = (Conn_Info_t*)
                     calloc(DEFAULT_SIZE_CONN, sizeof (Conn_Info_t));
               TBL->param = (Param_Info_t*)
                     calloc (DEFAULT_SIZE_PARAM, sizeof (Param_Info_t));
               TBL->inst_var = (Inst_Var_Info_t*)
                     calloc (DEFAULT_SIZE_INST_VAR, sizeof (Inst_Var_Info_t));
               TBL->defaults_var = (My_Value_t *)
                     calloc(DEFAULT_SIZE_DEFAULTS, sizeof (My_Value_t));
               if (! (TBL->conn && TBL->param &&
                      TBL->inst_var && TBL->defaults_var) ) {
                  fatal ("Could not allocate enough memory");
               } 
            }
#line 1798 "ifs_yacc.c"
    break;

  case 6: /* $@2: %empty  */
#line 617 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {context.table = TBL_NAME;}
#line 1804 "ifs_yacc.c"
    break;

  case 8: /* $@3: %empty  */
#line 620 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {context.table = TBL_PORT;
                 did_default_type = false;
                 did_allowed_types = false;
                 INIT (TBL->num_conn);}
#line 1813 "ifs_yacc.c"
    break;

  case 9: /* table: TOK_PORT_TABLE $@3 port_table  */
#line 625 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {TBL->num_conn = num_items;}
#line 1819 "ifs_yacc.c"
    break;

  case 10: /* $@4: %empty  */
#line 627 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {context.table = TBL_PARAMETER;
                 INIT (TBL->num_param);}
#line 1826 "ifs_yacc.c"
    break;

  case 11: /* table: TOK_PARAMETER_TABLE $@4 parameter_table  */
#line 630 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {TBL->num_param = num_items;}
#line 1832 "ifs_yacc.c"
    break;

  case 12: /* $@5: %empty  */
#line 632 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {context.table = TBL_STATIC_VAR;
                 INIT (TBL->num_inst_var);}
#line 1839 "ifs_yacc.c"
    break;

  case 13: /* table: TOK_STATIC_VAR_TABLE $@5 static_var_table  */
#line 635 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {TBL->num_inst_var = num_items;}
#line 1845 "ifs_yacc.c"
    break;

  case 16: /* name_table_item: TOK_C_FUNCTION_NAME identifier  */
#line 643 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {TBL->name.c_fcn_name =strdup (ifs_yytext);
               saw_function_name = true;
               if (parser_just_names && saw_model_name) return 0;}
#line 1853 "ifs_yacc.c"
    break;

  case 17: /* name_table_item: TOK_SPICE_MODEL_NAME identifier  */
#line 647 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {TBL->name.model_name = strdup (ifs_yytext);
               saw_model_name = true;
               if (parser_just_names && saw_function_name) return 0;}
#line 1861 "ifs_yacc.c"
    break;

  case 18: /* name_table_item: TOK_DESCRIPTION string  */
#line 651 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {TBL->name.description = strdup (ifs_yytext);}
#line 1867 "ifs_yacc.c"
    break;

  case 21: /* port_table_item: TOK_PORT_NAME list_of_ids  */
#line 659 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->conn[i].name = ITEM_BUF(i).str;
               }}
#line 1877 "ifs_yacc.c"
    break;

  case 22: /* port_table_item: TOK_DESCRIPTION list_of_strings  */
#line 665 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->conn[i].description = ITEM_BUF(i).str;
               }}
#line 1887 "ifs_yacc.c"
    break;

  case 23: /* port_table_item: TOK_DIRECTION list_of_directions  */
#line 671 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->conn[i].direction = ITEM_BUF(i).dir;
               }}
#line 1897 "ifs_yacc.c"
    break;

  case 24: /* port_table_item: TOK_DEFAULT_TYPE list_of_ctypes  */
#line 677 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               did_default_type = true;
               FOR_ITEM (i) {
                  TBL->conn[i].default_port_type = 
                 ITEM_BUF(i).ctype.kind;
                  TBL->conn[i].default_type = ITEM_BUF(i).ctype.id;
                  if (did_allowed_types) {
                 check_default_type (TBL->conn[i]);
                  }
               }}
#line 1913 "ifs_yacc.c"
    break;

  case 25: /* port_table_item: TOK_ALLOWED_TYPES list_of_ctype_lists  */
#line 689 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               did_allowed_types = true;
               FOR_ITEM (i) {
                  assign_ctype_list (&TBL->conn[i],
                         ITEM_BUF(i).ctype_list);
                  if (did_default_type) {
                 check_default_type (TBL->conn[i]);
                  }
               }}
#line 1928 "ifs_yacc.c"
    break;

  case 26: /* port_table_item: TOK_ARRAY list_of_bool  */
#line 700 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->conn[i].is_array = ITEM_BUF(i).btype;
               }}
#line 1938 "ifs_yacc.c"
    break;

  case 27: /* port_table_item: TOK_ARRAY_BOUNDS list_of_array_bounds  */
#line 706 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  ASSIGN_BOUNDS (conn, i);
                  assert (!TBL->conn[i].has_conn_ref);
               }}
#line 1949 "ifs_yacc.c"
    break;

  case 28: /* port_table_item: TOK_NULL_ALLOWED list_of_bool  */
#line 713 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->conn[i].null_allowed = ITEM_BUF(i).btype;
               }}
#line 1959 "ifs_yacc.c"
    break;

  case 31: /* parameter_table_item: TOK_PARAMETER_NAME list_of_ids  */
#line 725 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->param[i].name = ITEM_BUF(i).str;
               }}
#line 1969 "ifs_yacc.c"
    break;

  case 32: /* parameter_table_item: TOK_DESCRIPTION list_of_strings  */
#line 731 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->param[i].description = ITEM_BUF(i).str;
               }}
#line 1979 "ifs_yacc.c"
    break;

  case 33: /* parameter_table_item: TOK_DATA_TYPE list_of_dtypes  */
#line 737 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  check_dtype_not_pointer (ITEM_BUF(i).dtype);
                  TBL->param[i].type = ITEM_BUF(i).dtype;
               }}
#line 1990 "ifs_yacc.c"
    break;

  case 34: /* parameter_table_item: TOK_DEFAULT_VALUE list_of_default_values  */
#line 744 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {END; }
#line 1996 "ifs_yacc.c"
    break;

  case 35: /* parameter_table_item: TOK_LIMITS list_of_ranges  */
#line 746 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  assign_limits (TBL->param[i].type, 
                         &TBL->param[i],
                         ITEM_BUF(i).range);
               }}
#line 2008 "ifs_yacc.c"
    break;

  case 36: /* parameter_table_item: TOK_ARRAY list_of_bool  */
#line 754 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->param[i].is_array = ITEM_BUF(i).btype;
               }}
#line 2018 "ifs_yacc.c"
    break;

  case 37: /* parameter_table_item: TOK_ARRAY_BOUNDS list_of_array_bounds  */
#line 760 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  ASSIGN_BOUNDS (param, i);
               }}
#line 2028 "ifs_yacc.c"
    break;

  case 38: /* parameter_table_item: TOK_NULL_ALLOWED list_of_bool  */
#line 766 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->param[i].null_allowed = ITEM_BUF(i).btype;
               }}
#line 2038 "ifs_yacc.c"
    break;

  case 41: /* static_var_table_item: TOK_STATIC_VAR_NAME list_of_ids  */
#line 778 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->inst_var[i].name = ITEM_BUF(i).str;
               }}
#line 2048 "ifs_yacc.c"
    break;

  case 42: /* static_var_table_item: TOK_DESCRIPTION list_of_strings  */
#line 784 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->inst_var[i].description = ITEM_BUF(i).str;
               }}
#line 2058 "ifs_yacc.c"
    break;

  case 43: /* static_var_table_item: TOK_DATA_TYPE list_of_dtypes  */
#line 790 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->inst_var[i].type = ITEM_BUF(i).dtype;
               }}
#line 2068 "ifs_yacc.c"
    break;

  case 44: /* static_var_table_item: TOK_ARRAY list_of_bool  */
#line 796 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {int i;
               END;
               FOR_ITEM (i) {
                  TBL->inst_var[i].is_array = ITEM_BUF(i).btype;
               }}
#line 2078 "ifs_yacc.c"
    break;

  case 46: /* list_of_ids: list_of_ids identifier  */
#line 804 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                     {ITEM; BUF.str = (yyvsp[0].str);}
#line 2084 "ifs_yacc.c"
    break;

  case 48: /* list_of_array_bounds: list_of_array_bounds int_range  */
#line 809 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {ITEM; 
                BUF.range = (yyvsp[0].range);}
#line 2091 "ifs_yacc.c"
    break;

  case 49: /* list_of_array_bounds: list_of_array_bounds identifier  */
#line 812 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {ITEM; 
                BUF.range.is_named = true;
                BUF.range.u.name = (yyvsp[0].str);}
#line 2099 "ifs_yacc.c"
    break;

  case 51: /* list_of_strings: list_of_strings string  */
#line 818 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                     {ITEM; BUF.str = (yyvsp[0].str);}
#line 2105 "ifs_yacc.c"
    break;

  case 53: /* list_of_directions: list_of_directions direction  */
#line 822 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                           {ITEM; BUF.dir = (yyvsp[0].dir);}
#line 2111 "ifs_yacc.c"
    break;

  case 54: /* direction: TOK_DIR_IN  */
#line 825 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dir) = CMPP_IN;}
#line 2117 "ifs_yacc.c"
    break;

  case 55: /* direction: TOK_DIR_OUT  */
#line 826 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.dir) = CMPP_OUT;}
#line 2123 "ifs_yacc.c"
    break;

  case 56: /* direction: TOK_DIR_INOUT  */
#line 827 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.dir) = CMPP_INOUT;}
#line 2129 "ifs_yacc.c"
    break;

  case 58: /* list_of_bool: list_of_bool btype  */
#line 831 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                 {ITEM; BUF.btype = (yyvsp[0].btype);}
#line 2135 "ifs_yacc.c"
    break;

  case 60: /* list_of_ctypes: list_of_ctypes ctype  */
#line 835 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                   {ITEM; BUF.ctype = (yyvsp[0].ctype);}
#line 2141 "ifs_yacc.c"
    break;

  case 61: /* ctype: TOK_CTYPE_V  */
#line 838 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.ctype).kind = VOLTAGE;}
#line 2147 "ifs_yacc.c"
    break;

  case 62: /* ctype: TOK_CTYPE_VD  */
#line 839 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = DIFF_VOLTAGE;}
#line 2153 "ifs_yacc.c"
    break;

  case 63: /* ctype: TOK_CTYPE_VNAM  */
#line 840 "../../../../src/xspice/cmpp/ifs_yacc.y"
                             {(yyval.ctype).kind = VSOURCE_CURRENT;}
#line 2159 "ifs_yacc.c"
    break;

  case 64: /* ctype: TOK_CTYPE_I  */
#line 841 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = CURRENT;}
#line 2165 "ifs_yacc.c"
    break;

  case 65: /* ctype: TOK_CTYPE_ID  */
#line 842 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = DIFF_CURRENT;}
#line 2171 "ifs_yacc.c"
    break;

  case 66: /* ctype: TOK_CTYPE_G  */
#line 843 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = CONDUCTANCE;}
#line 2177 "ifs_yacc.c"
    break;

  case 67: /* ctype: TOK_CTYPE_GD  */
#line 844 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = DIFF_CONDUCTANCE;}
#line 2183 "ifs_yacc.c"
    break;

  case 68: /* ctype: TOK_CTYPE_H  */
#line 845 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = RESISTANCE;}
#line 2189 "ifs_yacc.c"
    break;

  case 69: /* ctype: TOK_CTYPE_HD  */
#line 846 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = DIFF_RESISTANCE;}
#line 2195 "ifs_yacc.c"
    break;

  case 70: /* ctype: TOK_CTYPE_D  */
#line 847 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = DIGITAL;}
#line 2201 "ifs_yacc.c"
    break;

  case 71: /* ctype: identifier  */
#line 848 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.ctype).kind = USER_DEFINED;
                     (yyval.ctype).id   = (yyvsp[0].str);}
#line 2208 "ifs_yacc.c"
    break;

  case 73: /* list_of_dtypes: list_of_dtypes dtype  */
#line 853 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                   {ITEM; BUF.dtype = (yyvsp[0].dtype);}
#line 2214 "ifs_yacc.c"
    break;

  case 74: /* dtype: TOK_DTYPE_REAL  */
#line 856 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                    {(yyval.dtype) = CMPP_REAL;}
#line 2220 "ifs_yacc.c"
    break;

  case 75: /* dtype: TOK_DTYPE_INT  */
#line 857 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dtype) = CMPP_INTEGER;}
#line 2226 "ifs_yacc.c"
    break;

  case 76: /* dtype: TOK_DTYPE_BOOLEAN  */
#line 858 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dtype) = CMPP_BOOLEAN;}
#line 2232 "ifs_yacc.c"
    break;

  case 77: /* dtype: TOK_DTYPE_COMPLEX  */
#line 859 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dtype) = CMPP_COMPLEX;}
#line 2238 "ifs_yacc.c"
    break;

  case 78: /* dtype: TOK_DTYPE_STRING  */
#line 860 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dtype) = CMPP_STRING;}
#line 2244 "ifs_yacc.c"
    break;

  case 79: /* dtype: TOK_DTYPE_POINTER  */
#line 861 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.dtype) = CMPP_POINTER;}
#line 2250 "ifs_yacc.c"
    break;

  case 81: /* list_of_ranges: list_of_ranges range  */
#line 865 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                   {ITEM; BUF.range = (yyvsp[0].range);}
#line 2256 "ifs_yacc.c"
    break;

  case 82: /* int_range: TOK_DASH  */
#line 868 "../../../../src/xspice/cmpp/ifs_yacc.y"
                           {(yyval.range).is_named = false; 
                    (yyval.range).u.bounds.lower.has_bound = false;
                    (yyval.range).u.bounds.upper.has_bound = false;}
#line 2264 "ifs_yacc.c"
    break;

  case 83: /* int_range: TOK_LBRACKET int_or_dash maybe_comma int_or_dash TOK_RBRACKET  */
#line 873 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {(yyval.range).is_named = false;
                (yyval.range).u.bounds.lower = (yyvsp[-3].bound);
                (yyval.range).u.bounds.upper = (yyvsp[-1].bound);}
#line 2272 "ifs_yacc.c"
    break;

  case 86: /* int_or_dash: TOK_DASH  */
#line 882 "../../../../src/xspice/cmpp/ifs_yacc.y"
                           {(yyval.bound).has_bound = false;}
#line 2278 "ifs_yacc.c"
    break;

  case 87: /* int_or_dash: integer_value  */
#line 883 "../../../../src/xspice/cmpp/ifs_yacc.y"
                              {(yyval.bound).has_bound = true; 
                           (yyval.bound).bound = (yyvsp[0].value);}
#line 2285 "ifs_yacc.c"
    break;

  case 88: /* range: TOK_DASH  */
#line 887 "../../../../src/xspice/cmpp/ifs_yacc.y"
                           {(yyval.range).is_named = false; 
                    (yyval.range).u.bounds.lower.has_bound = false;
                    (yyval.range).u.bounds.upper.has_bound = false;}
#line 2293 "ifs_yacc.c"
    break;

  case 89: /* range: TOK_LBRACKET number_or_dash maybe_comma number_or_dash TOK_RBRACKET  */
#line 892 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {(yyval.range).is_named = false;
                (yyval.range).u.bounds.lower = (yyvsp[-3].bound);
                (yyval.range).u.bounds.upper = (yyvsp[-1].bound);}
#line 2301 "ifs_yacc.c"
    break;

  case 90: /* number_or_dash: TOK_DASH  */
#line 897 "../../../../src/xspice/cmpp/ifs_yacc.y"
                               {(yyval.bound).has_bound = false;}
#line 2307 "ifs_yacc.c"
    break;

  case 91: /* number_or_dash: number  */
#line 898 "../../../../src/xspice/cmpp/ifs_yacc.y"
                     {(yyval.bound).has_bound = true; 
                  (yyval.bound).bound = (yyvsp[0].value);}
#line 2314 "ifs_yacc.c"
    break;

  case 92: /* list_of_pure_values: value  */
#line 902 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                 { (yyvsp[0].value).advance = 1; store_default_value(&(yyvsp[0].value)); }
#line 2320 "ifs_yacc.c"
    break;

  case 93: /* list_of_pure_values: list_of_pure_values value  */
#line 904 "../../../../src/xspice/cmpp/ifs_yacc.y"
                { (yyvsp[0].value).advance = 0; store_default_value(&(yyvsp[0].value)); }
#line 2326 "ifs_yacc.c"
    break;

  case 95: /* list_of_default_values: list_of_default_values value_or_dash  */
#line 909 "../../../../src/xspice/cmpp/ifs_yacc.y"
                { (yyvsp[0].value).advance = 1; store_default_value(&(yyvsp[0].value)); }
#line 2332 "ifs_yacc.c"
    break;

  case 97: /* value_or_dash: TOK_DASH  */
#line 913 "../../../../src/xspice/cmpp/ifs_yacc.y"
                               {(yyval.value).has_value = false;}
#line 2338 "ifs_yacc.c"
    break;

  case 99: /* value: string  */
#line 917 "../../../../src/xspice/cmpp/ifs_yacc.y"
                        {(yyval.value).has_value = true;
                     (yyval.value).kind = CMPP_STRING;
                     (yyval.value).u.svalue = (yyvsp[0].str);}
#line 2346 "ifs_yacc.c"
    break;

  case 100: /* value: btype  */
#line 920 "../../../../src/xspice/cmpp/ifs_yacc.y"
                        {(yyval.value).has_value = true;
                     (yyval.value).kind = CMPP_BOOLEAN;
                     (yyval.value).u.bvalue = (yyvsp[0].btype);}
#line 2354 "ifs_yacc.c"
    break;

  case 101: /* value: complex  */
#line 923 "../../../../src/xspice/cmpp/ifs_yacc.y"
                        {(yyval.value).has_value = true;
                     (yyval.value).kind = CMPP_COMPLEX;
                     (yyval.value).u.cvalue = (yyvsp[0].cval);}
#line 2362 "ifs_yacc.c"
    break;

  case 103: /* complex: TOK_LANGLE real maybe_comma real TOK_RANGLE  */
#line 930 "../../../../src/xspice/cmpp/ifs_yacc.y"
              {(yyval.cval).real = (yyvsp[-3].rval);
               (yyval.cval).imag = (yyvsp[-1].rval);}
#line 2369 "ifs_yacc.c"
    break;

  case 105: /* list_of_ctype_lists: list_of_ctype_lists delimited_ctype_list  */
#line 936 "../../../../src/xspice/cmpp/ifs_yacc.y"
                {ITEM; BUF.ctype_list = (yyvsp[0].ctype_list);}
#line 2375 "ifs_yacc.c"
    break;

  case 106: /* delimited_ctype_list: TOK_LBRACKET ctype_list TOK_RBRACKET  */
#line 939 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                                               {(yyval.ctype_list) = (yyvsp[-1].ctype_list);}
#line 2381 "ifs_yacc.c"
    break;

  case 107: /* ctype_list: ctype  */
#line 943 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {(yyval.ctype_list) = (Ctype_List_t*)calloc (1,
                            sizeof (Ctype_List_t));
                if (!(yyval.ctype_list)) {
                   fatal ("Error allocating memory");
                }
                (yyval.ctype_list)->ctype = (yyvsp[0].ctype);
                (yyval.ctype_list)->next = (Ctype_List_t*)0;}
#line 2393 "ifs_yacc.c"
    break;

  case 108: /* ctype_list: ctype_list maybe_comma ctype  */
#line 951 "../../../../src/xspice/cmpp/ifs_yacc.y"
               {(yyval.ctype_list) = (Ctype_List_t*)calloc (1, 
                            sizeof (Ctype_List_t));
                if (!(yyval.ctype_list)) {
                   fatal ("Error allocating memory");
                }
                (yyval.ctype_list)->ctype = (yyvsp[0].ctype);
                (yyval.ctype_list)->next = (yyvsp[-2].ctype_list);
                /*$$->next = (Ctype_List_t*)0;
                assert ($1);
                $1->next = $$;*/}
#line 2408 "ifs_yacc.c"
    break;

  case 109: /* btype: TOK_BOOL_YES  */
#line 963 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.btype) = true;}
#line 2414 "ifs_yacc.c"
    break;

  case 110: /* btype: TOK_BOOL_NO  */
#line 964 "../../../../src/xspice/cmpp/ifs_yacc.y"
                            {(yyval.btype) = false;}
#line 2420 "ifs_yacc.c"
    break;

  case 111: /* string: TOK_STRING_LITERAL  */
#line 967 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                     {(yyval.str) = strdup(ifs_yytext);}
#line 2426 "ifs_yacc.c"
    break;

  case 112: /* identifier: TOK_IDENTIFIER  */
#line 970 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                 {(yyval.str) = strdup(ifs_yytext);}
#line 2432 "ifs_yacc.c"
    break;

  case 113: /* number: real  */
#line 973 "../../../../src/xspice/cmpp/ifs_yacc.y"
                        {(yyval.value).has_value = true;
                 (yyval.value).kind = CMPP_REAL;
                 (yyval.value).u.rvalue = (yyvsp[0].rval);}
#line 2440 "ifs_yacc.c"
    break;

  case 115: /* integer_value: integer  */
#line 979 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                {(yyval.value).has_value = true;
                     (yyval.value).kind = CMPP_INTEGER;
                     (yyval.value).u.ivalue = (yyvsp[0].ival);}
#line 2448 "ifs_yacc.c"
    break;

  case 116: /* real: TOK_REAL_LITERAL  */
#line 984 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                   {(yyval.rval) = yydval;}
#line 2454 "ifs_yacc.c"
    break;

  case 117: /* integer: TOK_INT_LITERAL  */
#line 987 "../../../../src/xspice/cmpp/ifs_yacc.y"
                                   {(yyval.ival) = yyival;}
#line 2460 "ifs_yacc.c"
    break;


#line 2464 "ifs_yacc.c"

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

#line 990 "../../../../src/xspice/cmpp/ifs_yacc.y"

