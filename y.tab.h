/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     CHAR = 259,
     STR = 260,
     GET = 261,
     PUT = 262,
     VARIABLE = 263,
     FOR = 264,
     WHILE = 265,
     IF = 266,
     GETI = 267,
     GETC = 268,
     GETS = 269,
     PUTI = 270,
     PUTI_ = 271,
     PUTC = 272,
     PUTC_ = 273,
     PUTS = 274,
     PUTS_ = 275,
     FUNC = 276,
     RET = 277,
     CALL = 278,
     IFX = 279,
     ELSE = 280,
     OR = 281,
     AND = 282,
     NE = 283,
     EQ = 284,
     LE = 285,
     GE = 286,
     UMINUS = 287
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define CHAR 259
#define STR 260
#define GET 261
#define PUT 262
#define VARIABLE 263
#define FOR 264
#define WHILE 265
#define IF 266
#define GETI 267
#define GETC 268
#define GETS 269
#define PUTI 270
#define PUTI_ 271
#define PUTC 272
#define PUTC_ 273
#define PUTS 274
#define PUTS_ 275
#define FUNC 276
#define RET 277
#define CALL 278
#define IFX 279
#define ELSE 280
#define OR 281
#define AND 282
#define NE 283
#define EQ 284
#define LE 285
#define GE 286
#define UMINUS 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "c5.y"
{
    int iValue;        /* Integer value */
    char cValue;       /* Character value */
    char* sValue;      /* String value */
    /*char sIndex;       [> Symbol table index <]*/
    Node *nPtr;        /* Node pointer */
    char varName[13];  /* String value */
}
/* Line 1529 of yacc.c.  */
#line 122 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

