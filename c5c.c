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
/* Local variable count; TODO: remember to reset to 0! */
static int locVarCnt = 0;             
/* Parameter count; TODO: remember to reset to 0! */
static int paramCnt = 0;             
/* Indicating that we're parsing inside function definition */
static bool isInFunc = false;

/* Stack operations: increment or decrement */
typedef enum { opInc, opDec } spOpEnum;

/* Move SP (stack pointer) */
void mvSP(spOpEnum op) {
    printf("\tpush sp\n");
    printf("\tpush 1\n");
    switch(op) {
        case opInc:
            printf("\tadd\n");
            break;
        case opDec:
            printf("\tsub\n");
            break;
    }
    printf("\tpop sp\n");
}

/* Update variable info in hash table */
void updateVar(Node* node) {
    assert(node->nodeType = typeId);
    VarNode* varNode = &node->id;

    /*printf("Start updating...\n");*/
    VarNode* varEntry;

    /*printf("[c5c.c] updateVar(): %s dataType updated to %d\n", cpy->name, cpy->dataType);*/
    
    /*printf("Looking for {%s} in table...\n", varNode->name);*/
    HASH_FIND_STR( sym, varNode->name, varEntry );

    if (varEntry == NULL) {  /* Declaration */
        /* Create new hash table entry
         * (Necessary to prevent segfault) */
        varEntry = malloc(sizeof(VarNode));  /* Copy of var node */
        /* Name */
        strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
        /* Scope & Index */
        if (isInFunc) {
            varEntry->scope = typeLocal;
            varEntry->idx = locVarCnt++;
        } else {
            varEntry->scope = typeGlobal;
            varEntry->idx = glbVarCnt++;
        }
        HASH_ADD_STR( sym, name, varEntry );
        printf("\tpop\tsb[%d]\n", varEntry->idx);
    } else {  /* Update */
        printf("\tpop\tsb[%d]\n", varEntry->idx);
        mvSP(opDec);  /* Note: Need to decrement SP! */
    }
}

/* Get hash table entry */
VarNode* getVar(Node* node) {
    assert(node->nodeType == typeId);
    VarNode* varEntry = NULL;
    /*printf("Looking for %s...\n", n->id.name);*/
    HASH_FIND_STR( sym, node->id.name, varEntry );
    assert(varEntry != NULL);
    return varEntry;
}

/* TODO: Update function name */
void updateFunc(Node* node) {
    printf("[c5c.c] Updating Func!\n");
}

/* TODO: Add function parameter to hash table with correct index */
void addParam(VarNode* varNode) {
    /* Add parameter to hash table */
    printf("[c5c.c] Updating parameters!\n");
    VarNode* varEntry = malloc(sizeof(VarNode));
    /* Name */
    strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
    /* Datatype: unknown */
    /* Scope: local (use fp to address) */
    varEntry->scope = typeLocal;
    /* Index: Important! Index should decrease from -4 */
    varEntry->idx = (-4) - locVarCnt++;
    HASH_ADD_STR( sym, name, varEntry );
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

      case typeId:  /* Variables */
          /*printf("[c5c.c] Start typeID\n");*/
          assert(p->nodeType == typeId);
          p->id = *getVar(p);
          printf("\tpush\tsb[%d]\n", p->id.idx);
          /*printf("[c5c.c] End typeID\n");*/
          break;

      case typeOpr:  // Operators

        switch (p->opr.oper) {
            case GETI:  /* GET involves variable assignment */
                /* Step 1 (Note): Need to increment SP! */
                mvSP(opInc);
                /* Step 2: Push value */
                printf("\tgeti\n");
                /* Step 3: Call updateVar */
                updateVar(p->opr.op[0]);
                break;

            case GETC:
                mvSP(opInc);
                printf("\tgetc\n");
                updateVar(p->opr.op[0]);
                break;

            case GETS:
                mvSP(opInc);
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

            case '=':  /* Assignment operator */
              /* Step 1 (Note): Need to increment SP! */
              mvSP(opInc);
              /* Step 2: Push value (RHS) */
              ex(p->opr.op[1]);
              /* Step 3: Call updateVar to update hash table using the node */
              updateVar(p->opr.op[0]);
              break;

            case UMINUS:
              ex(p->opr.op[0]);
              printf("\tneg\n");
              break;
            
            /* 0:VARIABLE; 1:var_list, 2:stmt */
            case FUNC:  /* TODO: Function declaration */
              printf("[c5c.c] FUNC case\n");
              isInFunc = true;
              /*ex(p->opr.op[1]);  [> Deal with parameters <]*/
              /*ex(p->opr.op[2]);  [> Execute body <]*/
              isInFunc = false;
              /* TODO: Deal with var_list */
              /* TODO: Need a way to set up the label */
              break;

            /* 0:expr */
            case RET:  /* TODO: Return statement */
              printf("[c5c.c] RET case\n");
              break;

            /* 0:var_list; 1:VARIABLE */
            case ',':  /* TODO: Parameter list. */
              /* Parse from right to left! */
              printf("[c5c.c] var_list case\n");
              assert(p->opr.op[1]->nodeType == typeId);
              addParam(&p->opr.op[1]->id);
              /*ex(p->opr.op[0]);*/
              paramCnt = 0;  /* Reset */
              break;

            /* 0:VARIABLE 1:var_list */
            case CALL:  /* TODO: Function call */
              printf("[c5c.c] CALL case\n");
              /* TODO: Need a way to name->label... */
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
