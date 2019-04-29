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

/* Copy variable node into hash table for add/update,
 * and set datatypes for both the node and the copy. */
void updateVar(Node* var, dataEnum dataType) {
    /*printf("Start updating...\n");*/
    assert(var->nodeType == typeId);
    VarNode* cpy = malloc(sizeof(VarNode));
    VarNode* useless;

    /* Name */
    strncpy(cpy->name, var->id.name, strlen(var->id.name) + 1);
    /* Data type */
    var->dataType = dataType;
    cpy->dataType = dataType;
    /*printf("[c5c.c] updateVar(): %s dataType updated to %d\n", cpy->name, cpy->dataType);*/
    /* Scope */
    cpy->scope = typeGlobal;  /* TODO: Assume all global now... */
    /* Index */
    cpy->idx = glbVarCnt++;

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
    HASH_REPLACE_STR( sym, name, cpy, useless );
    /*printf("Hash table updated for %s of type %d\n", cpy->name, cpy->dataType);*/
}

VarNode* getVar(Node* n) {
    assert(n->nodeType == typeId);
    VarNode* var = NULL;
    /*printf("Looking for %s...\n", n->id.name);*/
    HASH_FIND_STR( sym, n->id.name, var );
    assert(var != NULL);
    n->id = *var;  /* Replace node from table */ 
    n->dataType = var->dataType;  /* Update data type */
    return var;
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
          printf("\tpush\tsb[%d]\n", getVar(p)->idx);
          /*printf("[c5c.c] End typeID\n");*/
          break;

      case typeOpr:  // Operators

        switch (p->opr.oper) {
            case GETI:
                printf("\tgeti\n");
                updateVar(p->opr.op[0], typeInt);
                break;

            case GETC:
                printf("\tgetc\n");
                updateVar(p->opr.op[0], typeChr);
                break;

            case GETS:
                printf("\tgets\n");
                updateVar(p->opr.op[0], typeStr);
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
              /*ex(p->opr.op[0]);*/
              /*printf("L%03d:\n", lblx = lbl++);*/
              /*ex(p->opr.op[1]);*/
              /*printf("\tjz\tL%03d\n", lbly = lbl++);*/
              /*ex(p->opr.op[3]);*/
              /*ex(p->opr.op[2]);*/
              /*printf("\tjmp\tL%03d\n", lblx);*/
              /*printf("L%03d:\n",       lbly);*/
              break;

            case WHILE:  // TODO
              /*printf("L%03d:\n", lbl1 = lbl++);*/
              /*ex(p->opr.op[0]);*/
              /*printf("\tjz\tL%03d\n", lbl2 = lbl++);*/
              /*ex(p->opr.op[1]);*/
              /*printf("\tjmp\tL%03d\n", lbl1);*/
              /*printf("L%03d:\n",       lbl2);*/
              break;

            case IF:  // TODO
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

            case '=':  /* Assignment operator */
              ex(p->opr.op[1]);
              /* Update hash table */
              updateVar(p->opr.op[0], p->opr.op[1]->dataType);
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
