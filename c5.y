%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"

Node* opr(int oper, int nops, ...);
Node* id(char* name);
Node* con(void* value, dataEnum type);
void freeNode(Node *p);
void mvSP(eSpOp op, int delta);
int ex(Node *p);
int yylex(void);
void yyerror(char *s);

VarNode* sym = NULL;  /* Hash table */


%}

%union {
    int iValue;        /* Integer value */
    char cValue;       /* Character value */
    char* sValue;      /* String value */
    Node *nPtr;        /* Node pointer */
    char varName[13];  /* String value */
};

%token <iValue> INTEGER
%token <cValue> CHAR
%token <sValue> STR GET PUT
%token <varName> VARIABLE
%token FOR WHILE IF
%token GETI GETC GETS
%token PUTI PUTI_ PUTC PUTC_ PUTS PUTS_
%token FUNC RET CALL MAIN
%token VAR_LS EXP_LS
%nonassoc IFX
%nonassoc ELSE

%left AND OR

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list var_list expr_list

%%

program:
        function                { /* exit(0); */ /* Commented for a second pass */ }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                             { $$ = opr(';', 2, NULL, NULL);     }
        | expr ';'                        { $$ = $1;                          }
        | GETI '(' VARIABLE ')' ';'       { $$ = opr(GETI, 1, id($3));        }
        | GETC '(' VARIABLE ')' ';'       { $$ = opr(GETC, 1, id($3));        }
        | GETS '(' VARIABLE ')' ';'       { $$ = opr(GETS, 1, id($3));        }
        | PUTI  '(' expr ')' ';'          { $$ = opr(PUTI,  1, $3);           }
        | PUTI_ '(' expr ')' ';'          { $$ = opr(PUTI_, 1, $3);           }
        | PUTC  '(' expr ')' ';'          { $$ = opr(PUTC,  1, $3);           }
        | PUTC_ '(' expr ')' ';'          { $$ = opr(PUTC_, 1, $3);           }
        | PUTS  '(' expr ')' ';'          { $$ = opr(PUTS,  1, $3);           }
        | PUTS_ '(' expr ')' ';'          { $$ = opr(PUTS_, 1, $3);           }
        | VARIABLE '=' expr ';'           { $$ = opr('=', 2, id($1), $3);     }
        | FOR '(' stmt stmt stmt ')' stmt { $$ = opr(FOR, 4, $3, $4, $5, $7); }
        | WHILE '(' expr ')' stmt         { $$ = opr(WHILE, 2, $3, $5);       }
        | IF '(' expr ')' stmt %prec IFX  { $$ = opr(IF, 2, $3, $5);          }
        | IF '(' expr ')' stmt ELSE stmt  { $$ = opr(IF, 3, $3, $5, $7);      }
        | '{' stmt_list '}'               { $$ = $2;                          }
        | FUNC VARIABLE '(' ')' stmt           { $$ = opr(FUNC, 2, id($2), $5); /* NEW */ }
        | FUNC VARIABLE '(' var_list ')' stmt  { $$ = opr(FUNC, 3, id($2), $4, $6); /* NEW */ }
        | RET expr ';'  { $$ = opr(RET, 1, $2); /* NEW */ }
        ;

stmt_list:
          stmt                  { $$ = $1;                  }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

var_list:
        var_list ',' VARIABLE  { $$ = opr(VAR_LS, 2, $1, id($3)); /* NEW */ }
        | VARIABLE             { $$ = id($1); }
        ;

expr_list:
         expr                  { $$ = $1;                     }
         | expr_list ',' expr  { $$ = opr(EXP_LS, 2, $1, $3); }
         ;

expr:
          INTEGER               { $$ = con(&$1, typeInt);   }
        | CHAR                  { $$ = con(&$1, typeChr);   }
        | STR                   { $$ = con($1, typeStr);    }
        | VARIABLE              { $$ = id($1);              }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2);  }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '%' expr         { $$ = opr('%', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3);  }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3);  }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3);  }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3);  }
        | expr AND expr		    { $$ = opr(AND, 2, $1, $3); }
        | expr OR expr		    { $$ = opr(OR, 2, $1, $3);  }
        | '(' expr ')'          { $$ = $2;                  }
        | VARIABLE '(' ')'            { $$ = opr(CALL, 1, id($1)); /* NEW */}
        | VARIABLE '(' expr_list ')'  { $$ = opr(CALL, 2, id($1), $3); /* NEW */}
        ;

%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

Node* con(void* value, dataEnum dataType) {
    Node* p;
    size_t nodeSize;

    /* Allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(ConstNode);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* Copy information */
    p->nodeType = typeCon;
    p->con.dataType = dataType;
    switch (dataType) {
        case typeInt:
            p->con.iVal = *((int*) value);
            break;
        case typeChr: 
            p->con.cVal = *((char*) value); 
            break;
        case typeStr:
            p->con.sVal = (char*) value;
            break;
    }

    /*printf("Making con of type [%d]\n", dataType);*/

    return p;
}

Node* id(char* name) {
    Node* p;
    size_t nodeSize;

    /* Allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(VarNode);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* Set type */
    p->nodeType = typeId;
    /* Set name */
    strncpy(p->id.name, name, strlen(name) + 1);

    /*printf("[c5.y] created ID: %s\n", name);*/

    return p;
}

Node* opr(int oper, int nops, ...) {
    va_list ap;
    Node* p;
    size_t nodeSize;
    int i;

    /* Allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(OprNode) +
        (nops - 1) * sizeof(Node*);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* Copy information */
    p->nodeType = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, Node*);
    va_end(ap);
    return p;
}

void freeNode(Node *p) {
    int i;

    if (!p) return;
    if (p->nodeType == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv) {
    extern FILE* yyin;
    yyin = fopen(argv[1], "r");
    /* Pre-allocate stack space for 1000 global variables */
    mvSp(opInc, 1000);
    /* Jump immediately to Main (L999) */
    printf("jmp L999\n");
    yyparse();
    return 0;
}
