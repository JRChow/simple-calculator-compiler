%{
#include <stdlib.h>
#include <string.h>
#include "calc3.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

">="     return GE;
"<="     return LE;
"=="     return EQ;
"!="     return NE;
"for"    return FOR;
"while"  return WHILE;
"if"     return IF;
"else"   return ELSE;
"&&"     return AND;
"||"     return OR;

"geti"   return GETI;
"getc"   return GETC;
"gets"   return GETS;

"puti"   return PUTI;
"puti_"  return PUTI_;
"putc"   return PUTC;
"putc_"  return PUTC_;
"puts"   return PUTS;
"puts_"  return PUTS_;

"func"   return FUNC;
"return" return RET;

[a-zA-Z][a-zA-Z0-9]*  { 
                        strncpy(yylval.varName, yytext, strlen(yytext) + 1);
                        /*yylval.strVal = yytext;*/
                        /*printf("[c5.l] Matched variable: dest = %s, src = %s\n", yylval.varName, yytext);*/
                        return VARIABLE;
                      }

0             {
                  yylval.iValue = atoi(yytext);
                  return INTEGER;
              }

[1-9][0-9]*   {
                  yylval.iValue = atoi(yytext);
                  return INTEGER;
              }

\'.*\'        {
                  /* TODO: deal with empty char */
                  /* Just cast char into int to get ASCII value */
                  yylval.cValue = yytext[1];
                  /*yylval.iValue = (int) yytext[1];*/
                  return CHAR;
              }

\".*\"        {
                  /* Length of the inside string */
                  int sLen = strlen(yytext) - 2;
                  if (sLen == 0) {  /* Empty string "" */
                      yylval.sValue = "";
                  } else {  /* Non-empty string */
                      char* cpy = (char*) calloc( sLen + 1, sizeof(char) );
                      memcpy(cpy, &yytext[1], sLen);
                      cpy[sLen] = '\0';
                      yylval.sValue = cpy;
                      /*printf("[c5.l] Match String: %s\n", cpy);*/
                  }
                  return STR;
              }

[-()<>=+*/;{}.%]  return *yytext;


\/\/.*\n	    ;    /* Skip comments */

[ \t\n]+        ;    /* Ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
