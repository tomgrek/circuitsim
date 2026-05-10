/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MOD_YACC_H_INCLUDED
# define YY_YY_MOD_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_ARGS = 258,                /* TOK_ARGS  */
    TOK_INIT = 259,                /* TOK_INIT  */
    TOK_CALLBACK = 260,            /* TOK_CALLBACK  */
    TOK_ANALYSIS = 261,            /* TOK_ANALYSIS  */
    TOK_NEW_TIMEPOINT = 262,       /* TOK_NEW_TIMEPOINT  */
    TOK_TIME = 263,                /* TOK_TIME  */
    TOK_RAD_FREQ = 264,            /* TOK_RAD_FREQ  */
    TOK_TEMPERATURE = 265,         /* TOK_TEMPERATURE  */
    TOK_T = 266,                   /* TOK_T  */
    TOK_PARAM = 267,               /* TOK_PARAM  */
    TOK_PARAM_SIZE = 268,          /* TOK_PARAM_SIZE  */
    TOK_PARAM_NULL = 269,          /* TOK_PARAM_NULL  */
    TOK_PORT_SIZE = 270,           /* TOK_PORT_SIZE  */
    TOK_PORT_NULL = 271,           /* TOK_PORT_NULL  */
    TOK_PARTIAL = 272,             /* TOK_PARTIAL  */
    TOK_AC_GAIN = 273,             /* TOK_AC_GAIN  */
    TOK_CHANGED = 274,             /* TOK_CHANGED  */
    TOK_OUTPUT_DELAY = 275,        /* TOK_OUTPUT_DELAY  */
    TOK_STATIC_VAR = 276,          /* TOK_STATIC_VAR  */
    TOK_STATIC_VAR_SIZE = 277,     /* TOK_STATIC_VAR_SIZE  */
    TOK_STATIC_VAR_INST = 278,     /* TOK_STATIC_VAR_INST  */
    TOK_INPUT = 279,               /* TOK_INPUT  */
    TOK_INPUT_STRENGTH = 280,      /* TOK_INPUT_STRENGTH  */
    TOK_INPUT_STATE = 281,         /* TOK_INPUT_STATE  */
    TOK_INPUT_TYPE = 282,          /* TOK_INPUT_TYPE  */
    TOK_OUTPUT = 283,              /* TOK_OUTPUT  */
    TOK_OUTPUT_CHANGED = 284,      /* TOK_OUTPUT_CHANGED  */
    TOK_OUTPUT_STRENGTH = 285,     /* TOK_OUTPUT_STRENGTH  */
    TOK_OUTPUT_STATE = 286,        /* TOK_OUTPUT_STATE  */
    TOK_OUTPUT_TYPE = 287,         /* TOK_OUTPUT_TYPE  */
    TOK_COMMA = 288,               /* TOK_COMMA  */
    TOK_LPAREN = 289,              /* TOK_LPAREN  */
    TOK_RPAREN = 290,              /* TOK_RPAREN  */
    TOK_LBRACKET = 291,            /* TOK_LBRACKET  */
    TOK_RBRACKET = 292,            /* TOK_RBRACKET  */
    TOK_MISC_C = 293,              /* TOK_MISC_C  */
    TOK_IDENTIFIER = 294,          /* TOK_IDENTIFIER  */
    TOK_LOAD = 295,                /* TOK_LOAD  */
    TOK_TOTAL_LOAD = 296,          /* TOK_TOTAL_LOAD  */
    TOK_MESSAGE = 297,             /* TOK_MESSAGE  */
    TOK_CALL_TYPE = 298            /* TOK_CALL_TYPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TOK_ARGS 258
#define TOK_INIT 259
#define TOK_CALLBACK 260
#define TOK_ANALYSIS 261
#define TOK_NEW_TIMEPOINT 262
#define TOK_TIME 263
#define TOK_RAD_FREQ 264
#define TOK_TEMPERATURE 265
#define TOK_T 266
#define TOK_PARAM 267
#define TOK_PARAM_SIZE 268
#define TOK_PARAM_NULL 269
#define TOK_PORT_SIZE 270
#define TOK_PORT_NULL 271
#define TOK_PARTIAL 272
#define TOK_AC_GAIN 273
#define TOK_CHANGED 274
#define TOK_OUTPUT_DELAY 275
#define TOK_STATIC_VAR 276
#define TOK_STATIC_VAR_SIZE 277
#define TOK_STATIC_VAR_INST 278
#define TOK_INPUT 279
#define TOK_INPUT_STRENGTH 280
#define TOK_INPUT_STATE 281
#define TOK_INPUT_TYPE 282
#define TOK_OUTPUT 283
#define TOK_OUTPUT_CHANGED 284
#define TOK_OUTPUT_STRENGTH 285
#define TOK_OUTPUT_STATE 286
#define TOK_OUTPUT_TYPE 287
#define TOK_COMMA 288
#define TOK_LPAREN 289
#define TOK_RPAREN 290
#define TOK_LBRACKET 291
#define TOK_RBRACKET 292
#define TOK_MISC_C 293
#define TOK_IDENTIFIER 294
#define TOK_LOAD 295
#define TOK_TOTAL_LOAD 296
#define TOK_MESSAGE 297
#define TOK_CALL_TYPE 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 323 "../../../../src/xspice/cmpp/mod_yacc.y"

   char *str;
   Sub_Id_t sub_id;

#line 158 "mod_yacc.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MOD_YACC_H_INCLUDED  */
