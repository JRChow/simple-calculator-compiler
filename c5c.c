#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "calc3.h"
#include "y.tab.h"

/* Label */
static int label = 0;
/* Global variable count */
static int glbVarCnt = 0;             
/* Local variable count */
static int locVarCnt = 0;             
/* Parameter count */
static int paramCnt = 0;             
/* Argument count */
static int argCnt = 0;             
/* Parsing state */
static eParseState pState = sGlobal;

/* Move SP (stack pointer) */
void mvSP(eSpOp op, int delta) {
    printf("\tpush\tsp\n");
    printf("\tpush\t%d\n", delta);
    switch(op) {
        case opInc:
            printf("\tadd\n");
            break;
        case opDec:
            printf("\tsub\n");
            break;
    }
    printf("\tpop\tsp\n");
}

/* [IMPORTANT] */
/* Update variable info in hash table AND stack */
void updateVar(Node* node) {
    assert(node->nodeType = typeId);
    VarNode* varNode = &node->id;

    /*printf("Start updating...\n");*/
    VarNode* varEntry;

    /*printf("[c5c.c] updateVar(): %s dataType updated to %d\n", cpy->name, cpy->dataType);*/
    
    /*printf("Looking for {%s} in table...\n", varNode->name);*/
    switch(pState) {
        case sGlobal:
            HASH_FIND_STR( globalVarTable, varNode->name, varEntry );
            break;
        default:
            HASH_FIND_STR( localVarTable, varNode->name, varEntry );
    }

    if (varEntry == NULL) {  /* Declaration */
        /* Create new hash table entry 
         * (deep copy necessary to prevent segfault) */
        varEntry = malloc(sizeof(VarNode));  /* Copy of var node */
        /* Copy name */
        strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
        /* Determine offset & update hash table */
        switch(pState) {
            case sGlobal:
                varEntry->offset = glbVarCnt++;
                HASH_ADD_STR( globalVarTable, name, varEntry );
                break;
            case sFuncParam:
                varEntry->offset = -(4 + paramCnt++);
                HASH_ADD_STR( localVarTable, name, varEntry );
                break;
            case sFuncBody:
                varEntry->offset = locVarCnt++;
                HASH_ADD_STR( localVarTable, name, varEntry );
                break;
        }
        /*printf("updateVar() [S%d] added var %s to table\n", pState, varEntry->name);*/
    } 
    /* Update stack */
    switch(pState) {
        case sGlobal:
            printf("\tpop\tsb[%d]\n", varEntry->offset);
            break;
        case sFuncParam:
            /* Do NOT update stack for function parameters */
            break;
        case sFuncBody:
            printf("\tpop\tfp[%d]\n", varEntry->offset);
            break;
    }
}

/* Reference variable */
void getVar(Node* node) {
    assert(node->nodeType == typeId);
    VarNode* varNode = &node->id;
    VarNode* varEntry = NULL;
    switch(pState) {
        case sGlobal:
            /*printf("getVar() [global] Looking for %s in global table\n", varNode->name);*/
            HASH_FIND_STR( globalVarTable, varNode->name, varEntry );
            printf("\tpush\tsb[%d]\n", varEntry->offset);
            break;
        case sFuncParam:
            /*printf("funcParam ~ getVar(%s)\n", varNode->name);*/
            varEntry = malloc(sizeof(VarNode));
            strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
            varEntry->offset = -(4 + paramCnt++);
            HASH_ADD_STR( localVarTable, name, varEntry );
            /*printf("getVar() [param] %s added to local table\n", varNode->name);*/
            break;
        case sFuncBody:
            /* First, query local var table */
            /*printf("getVar() [S%d] Looking for %s in local table\n", pState, varNode->name);*/
            HASH_FIND_STR( localVarTable, varNode->name, varEntry );

            if (varEntry != NULL) {  /* If found local variable */
                printf("\tpush\tfp[%d]\n", varEntry->offset);
            } else {  /* If not found, add to global variable table */
                /*printf("getVar() %s not found in local table\n", varNode->name);*/
                varEntry = malloc(sizeof(VarNode));
                strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
                varEntry->offset = glbVarCnt++;
                HASH_ADD_STR( globalVarTable, name, varEntry );
                printf("\tpush\tsb[%d]\n", varEntry->offset);
            }
            break;
    }
}

/* Get function label */
int getFuncLabel(Node* node) {
    assert(node->nodeType == typeId);
    VarNode* varNode = &node->id;
    /*printf("getFuncLabel(%s)\n", varNode->name);*/
    FuncInfo* funcEntry;
    HASH_FIND_STR ( funcTable, varNode->name, funcEntry );
    /* If function name not found, create new entry */
    if (funcEntry == NULL) {
        /*printf("--- entry not found for func %s\n", varNode->name);*/
        funcEntry = malloc(sizeof(FuncInfo));
        strncpy(funcEntry->name, varNode->name, strlen(varNode->name) + 1);
        funcEntry->label = label++;
        HASH_ADD_STR ( funcTable, name, funcEntry );
    }
    return funcEntry->label;
}


int ex(Node *p) {
  int labelx, labely, label1, label2;

  if (!p) return 0;

  switch (p->nodeType) {
      case typeCon:  /* Constants */
          switch (p->con.dataType) {
              case typeInt:
                  printf("\tpush\t%d\n", p->con.iVal);
                  break;
              case typeChr:
                  printf("\tpush\t'%c'\n", p->con.cVal);
                  break;
              case typeStr:
                  printf("\tpush\t\"%s\"\n", p->con.sVal);
                  break;
          }
          break;

      case typeId:  /* Variable references */
          /*printf("[c5c.c] Start typeID\n");*/
          assert(p->nodeType == typeId);
          getVar(p);
          /*printf("[c5c.c] End typeID\n");*/
          break;

      case typeOpr:  // Operators

        switch (p->opr.oper) {
            case GETI:  /* GET involves variable assignment */
                /* Step 1: Push value */
                printf("\tgeti\n");
                /* Step 2: Call updateVar */
                updateVar(p->opr.op[0]);
                break;

            case GETC:
                printf("\tgetc\n");
                updateVar(p->opr.op[0]);
                break;

            case GETS:
                printf("\tgets\n");
                updateVar(p->opr.op[0]);
                break;

            case PUTI:
                ex(p->opr.op[0]);
                printf("\tputi\n");
                break;

            case PUTI_:
                ex(p->opr.op[0]);
                printf("\tputi_\n");
                break;

            case PUTC:
                ex(p->opr.op[0]);
                printf("\tputc\n");
                break;

            case PUTC_:
                ex(p->opr.op[0]);
                printf("\tputc_\n");
                break;

            case PUTS:
                ex(p->opr.op[0]);
                printf("\tputs\n");
                break;

            case PUTS_:
                ex(p->opr.op[0]);
                printf("\tputs_\n");
                break;

            case FOR:
                ex(p->opr.op[0]);  /* Execute initialization */
                /* Label for condition check */
                printf("L%03d:\n", labelx = label++);
                ex(p->opr.op[1]);  /* Execute condition */
                /* If condition fails, jump to the end */
                printf("\tj0\tL%03d\n", labely = label++);
                /* If condition holds, execute body */
                ex(p->opr.op[3]);
                ex(p->opr.op[2]);  /* Execute increment */
                /* Check condition */
                printf("\tjmp\tL%03d\n", labelx);
                printf("L%03d:\n",       labely);  /* The end */
              break;

            case WHILE:
              printf("L%03d:\n", label1 = label++);
              ex(p->opr.op[0]);  /* Execute condition */
              /* If condition fails, jump to the end */
              printf("\tj0\tL%03d\n", label2 = label++);
              ex(p->opr.op[1]);  /* Execute body */
              /* Go back to loop start to check condition */
              printf("\tjmp\tL%03d\n", label1);
              printf("L%03d:\n",       label2);  /* The end */
              break;

            case IF:
              ex(p->opr.op[0]);  /* Handle condition */

              if (p->opr.nops > 2) {  /* if-else type */
                  /* If condition fails, jump to "else" */
                  printf("\tj0\tL%03d\n", label1 = label++);
                  ex(p->opr.op[1]);  /* Execute "then" branch */
                  /* Jump to the end of statement */
                  printf("\tjmp\tL%03d\n", label2 = label++);
                  /* Start of the "else" branch */
                  printf("L%03d:\n",       label1);
                  ex(p->opr.op[2]);  /* Execute "else" branch */
                  printf("L%03d:\n", label2);  /* End of statement */
              } else {                /* if type */
                  /* If condition fails, jump to the end */
                  printf("\tj0\tL%03d\n", label1 = label++);
                  ex(p->opr.op[1]);
                  printf("L%03d:\n", label1);  /* The end */
              }
              break;

            /* [IMPORTANT] */
            case '=':  /* Assignment operator */
              /* 0. Push value (RHS) */
              ex(p->opr.op[1]);
              /* 1. Call updateVar to update hash table using the node */
              updateVar(p->opr.op[0]);
              break;

            case UMINUS:
              ex(p->opr.op[0]);
              printf("\tneg\n");
              break;
            
            /* [IMPORTANT] */
            /* 0:VARIABLE; 1:var_list, 2:stmt */
            case FUNC:  /* Function declaration */
              /*printf("[c5c.c] FUNC case\n");*/
              /* 0. Determine function label */
              printf("L%03d:\n", getFuncLabel(p->opr.op[0]));
              /* 1. Pre-allocate stack space for 100 local variables */
              mvSP(opInc, 100);
              if (p->opr.nops == 2) {  /* No parameter */
                  /* 2. Enter function body */
                  pState = sFuncBody;
                  locVarCnt = 0;
                  ex(p->opr.op[1]);
              } else {  /* Have >= 1 parameter */
                  assert(p->opr.nops == 3);
                  /* 2. Parse parameters into local var table */
                  pState = sFuncParam;
                  paramCnt = 0;
                  /* Note parameter list can be empty */
                  if (p->opr.op[1] != NULL) {
                      ex(p->opr.op[1]);
                  }
                  /* 3. Enter function body */
                  pState = sFuncBody;
                  locVarCnt = 0;
                  ex(p->opr.op[2]);
              }
              pState = sGlobal;
              /* Clear local var table */
              HASH_CLEAR(hh, localVarTable);
              /*printf("local var table cleared\n");*/
              locVarCnt = 0;
              printf("\tret\n");  /* In case there's no return statement */
              break;

            /* 0:expr */
            case RET:  /* Return statement */
              /*printf("[c5c.c] RET case\n");*/
              ex(p->opr.op[0]);
              printf("\tret\n");
              break;

            case MAIN:
              printf("L999:\n");
              ex(p->opr.op[0]);
              break;

            case VAR_LS:  /* Parameter list (for function definition) */
              /*printf("[c5c.c] var_list \n");*/
              assert(pState == sFuncParam);
              /* For function definition, parse from right to left */
              updateVar(p->opr.op[1]);
              ex(p->opr.op[0]);
              break;

            case EXP_LS:  /* Expression list (for function calls) */
              /*printf("[c5c.c] expr_list case\n");*/
              /* For function calls, parse from left to right */
              ex(p->opr.op[0]);
              ex(p->opr.op[1]);
              argCnt++;
              break;

            /* 0:VARIABLE 1:var_list */
            /* [IMPORTANT] */
            case CALL:  /* Function call */
              /*printf("[c5c.c] CALL case\n");*/
              if (p->opr.nops == 1) {  /* No argument */
                  printf("\tcall\tL%03d, %d\n", getFuncLabel(p->opr.op[0]), 0);
              } else {  /* Have >= 1 argument */
                  assert(p->opr.nops == 2);
                  /* Push expr_list from left to right to stack */
                  argCnt = 1;  /* Not 0! */
                  ex(p->opr.op[1]);
                  printf("\tcall\tL%03d, %d\n", getFuncLabel(p->opr.op[0]), argCnt);
              }
              break;

            default:
              ex(p->opr.op[0]);
              ex(p->opr.op[1]);

              switch (p->opr.oper) {
                  case '+':   printf("\tadd\n"); break;

                  case '-':   printf("\tsub\n"); break;

                  case '*':   printf("\tmul\n"); break;

                  case '/':   printf("\tdiv\n"); break;

                  case '%':   printf("\tmod\n"); break;

                  case '<':   printf("\tcomplt\n"); break;

                  case '>':   printf("\tcompgt\n"); break;

                  case GE:    printf("\tcompge\n"); break;

                  case LE:    printf("\tcomple\n"); break;

                  case NE:    printf("\tcompne\n"); break;

                  case EQ:    printf("\tcompeq\n"); break;

                  case AND:   printf("\tand\n"); break;

                  case OR:    printf("\tor\n"); break;
              }
        }
  }
  return 0;
}
