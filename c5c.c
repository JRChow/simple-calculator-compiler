#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "calc3.h"
#include "y.tab.h"

/* Label */
static int lbl;

/* Global variable count */
int glbVarCnt = 0;             

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
    varNode->dataType = node->dataType;

    /*printf("Start updating...\n");*/
    VarNode* varEntry;
    /*VarNode* useless;*/

    /*printf("[c5c.c] updateVar(): %s dataType updated to %d\n", cpy->name, cpy->dataType);*/
    /*printf("Looking for {%s} in table...\n", varNode->name);*/
    HASH_FIND_STR( sym, varNode->name, varEntry );
    if (varEntry == NULL) {  /* Declaration */
        /*printf("New declaration\n");*/
        /* Use the node as a hash table entry */
        /*varEntry = varNode;*/
        /* Create new hash table entry
         * (Necessary to prevent segfault) */
        varEntry = malloc(sizeof(VarNode));  /* Copy of var node */
        /* Name */
        strncpy(varEntry->name, varNode->name, strlen(varNode->name) + 1);
        /* Data type */
        varEntry->dataType = varNode->dataType;
        /* Scope */
        varEntry->scope = typeGlobal;  /* TODO: Assume all global for now... */
        /* Index */
        varEntry->idx = glbVarCnt++;
        /*varEntry->scope = typeGlobal;*/
        HASH_ADD_STR( sym, name, varEntry );
        printf("\tpop\tsb[%d]\n", varEntry->idx);
    } else {  /* Update */
        // printf("Update existing entry\n");
        printf("\tpop\tsb[%d]\n", varEntry->idx);
        /* Note: Need to decrement SP! */
        mvSP(opDec);
    }
    /*printf("Done updating\n");*/
    /* Data type */
    /*varEntry->dataType = varNode->dataType;*/
    /*HASH_REPLACE_STR( sym, name, varEntry, useless );*/
    /*cpy->idx = glbVarCnt++;*/

    /*printf("Updating variable %s\n", var->name);*/
    /*[>VarNode* varBlock = malloc(sizeof(VarNode));<]*/
    /*[>varBlock->name = var->id.name;<]*/
    /*[>strncpy(varBlock->name, var->id.name, strlen(var->id.name) + 1);<]*/
    /*[>printf("Name copied\n");<]*/
    /*var->dataType = right->dataType;*/
    /*var->dataType = right->dataType;*/
    /*printf("Datatype updated\n");*/
    /*[>var->dataType = exp->dataType;<]*/
    /*var->scope = typeGlobal;  */
    /*printf("Scope updated\n");*/
    /*var->idx = glbVarCnt++;*/
    /*printf("Idx updated\n");*/
    /*printf("Structure created\n");*/

    /*printf("Start hash table operation...");*/
    /*printf("Hash table updated for %s : %d to idx %d\n", cpy->name, cpy->dataType, cpy->idx);*/
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


int ex(Node *p) {
  int lblx, lbly, lbl1, lbl2;

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
          p->dataType = p->id.dataType;
          printf("\tpush\tsb[%d]\n", p->id.idx);
          /*printf("[c5c.c] End typeID\n");*/
          break;

      case typeOpr:  // Operators

        switch (p->opr.oper) {
            case GETI:  /* GET involves variable assignment */
                /* Step 1: Update varNode datatype */
                p->opr.op[0]->dataType = typeInt;
                /* Step 2 (Note): Need to increment SP! */
                mvSP(opInc);
                /* Step 3: Push value */
                printf("\tgeti\n");
                /* Step 4: Call updateVar to update hash table using the node */
                updateVar(p->opr.op[0]);
                break;

            case GETC:
                p->opr.op[0]->dataType = typeChr;
                mvSP(opInc);
                printf("\tgetc\n");
                updateVar(p->opr.op[0]);
                break;

            case GETS:
                p->opr.op[0]->dataType = typeStr;
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

            case FOR:  // TODO
                ex(p->opr.op[0]);  /* Execute initialization */
                /* Label for condition check */
                printf("L%03d:\n", lblx = lbl++);
                ex(p->opr.op[1]);  /* Execute condition */
                /* If condition fails, jump to the end */
                printf("\tj0\tL%03d\n", lbly = lbl++);
                /* If condition holds, execute body */
                ex(p->opr.op[3]);
                ex(p->opr.op[2]);  /* Execute increment */
                /* Check condition */
                printf("\tjmp\tL%03d\n", lblx);
                printf("L%03d:\n",       lbly);  /* The end */
              break;

            case WHILE:
              printf("L%03d:\n", lbl1 = lbl++);
              ex(p->opr.op[0]);  /* Execute condition */
              /* If condition fails, jump to the end */
              printf("\tj0\tL%03d\n", lbl2 = lbl++);
              ex(p->opr.op[1]);  /* Execute body */
              /* Go back to loop start to check condition */
              printf("\tjmp\tL%03d\n", lbl1);
              printf("L%03d:\n",       lbl2);  /* The end */
              break;

            case IF:
              ex(p->opr.op[0]);  /* Handle condition */

              if (p->opr.nops > 2) {  /* if-else type */
                  /* If condition fails, jump to "else" */
                  printf("\tj0\tL%03d\n", lbl1 = lbl++);
                  ex(p->opr.op[1]);  /* Execute "then" branch */
                  /* Jump to the end of statement */
                  printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                  /* Start of the "else" branch */
                  printf("L%03d:\n",       lbl1);
                  ex(p->opr.op[2]);  /* Execute "else" branch */
                  printf("L%03d:\n", lbl2);  /* End of statement */
              } else {                /* if type */
                  /* If condition fails, jump to the end */
                  printf("\tj0\tL%03d\n", lbl1 = lbl++);
                  ex(p->opr.op[1]);
                  printf("L%03d:\n", lbl1);  /* The end */
              }
              break;

            case '=':  /* FIXME: Assignment operator */
              /*printf("[c5c.c] Match '='\n");*/
              /* Step 1: Update varNode datatype */
              p->opr.op[0]->dataType = p->opr.op[1]->dataType;
              /* Step 2 (Note): Need to increment SP! */
              mvSP(opInc);
              /* Step 3: Push value (RHS) */
              ex(p->opr.op[1]);
              /* Step 4: Call updateVar to update hash table using the node */
              updateVar(p->opr.op[0]);
              break;

            case UMINUS:
              ex(p->opr.op[0]);
              printf("\tneg\n");
              break;

            default:
              p->dataType = typeInt;
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
