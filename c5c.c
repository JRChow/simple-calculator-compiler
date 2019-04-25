#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

// Label
static int lbl;

int ex(nodeType *p) {
  int lblx, lbly, lbl1, lbl2;

  if (!p) return 0;

  switch (p->type) {
      case typeCon:  /* Constants */
          printf("\tpush\t%d\n", p->con.value);
          break;

      case typeId:  // Variables
        /*printf("\tpush\t%c\n", p->id.i + 'a');*/
        break;

      case typeOpr:  // Operators

        switch (p->opr.oper) {
            case FOR:
              /*ex(p->opr.op[0]);*/
              /*printf("L%03d:\n", lblx = lbl++);*/
              /*ex(p->opr.op[1]);*/
              /*printf("\tjz\tL%03d\n", lbly = lbl++);*/
              /*ex(p->opr.op[3]);*/
              /*ex(p->opr.op[2]);*/
              /*printf("\tjmp\tL%03d\n", lblx);*/
              /*printf("L%03d:\n",       lbly);*/
              break;

            case WHILE:
              /*printf("L%03d:\n", lbl1 = lbl++);*/
              /*ex(p->opr.op[0]);*/
              /*printf("\tjz\tL%03d\n", lbl2 = lbl++);*/
              /*ex(p->opr.op[1]);*/
              /*printf("\tjmp\tL%03d\n", lbl1);*/
              /*printf("L%03d:\n",       lbl2);*/
              break;

            case IF:
              /*ex(p->opr.op[0]);  // Handle condition*/

              /*if (p->opr.nops > 2) {  [> if-else <]*/
                /*printf("\tj0\tL%03d\n", lbl1 = lbl++);*/
                /*ex(p->opr.op[1]);  // "then" branch*/
                /*printf("\tjmp\tL%03d\n", lbl2 = lbl++);*/
                /*printf("L%03d:\n",       lbl1);  // "else" branch*/
                /*ex(p->opr.op[2]);*/
                /*printf("L%03d:\n", lbl2);  // End of statement*/
              /*} else {  [> if <]*/
                /*printf("\tjz\tL%03d\n", lbl1 = lbl++);*/
                /*ex(p->opr.op[1]);*/
                /*printf("L%03d:\n", lbl1);*/
              /*}*/
              break;

            case READ:
              printf("\tgeti\n");
              /*printf("\tread\n");*/
              /*printf("\tpop\t%c\n", p->opr.op[0]->id.i + 'a');*/
              break;

            case PRINT:
              // TODO: put* depends on the type... default to int just for now
              //       dunno if the type is already encoded in the current struct
              //       if not, needa modify the struct definition...
              //       Update: ok there's only int and var now, needa add char & string,
              //               working on that right now!
              ex(p->opr.op[0]);
              printf("\tputi\n");
              break;

            case '=':
              /*ex(p->opr.op[1]);*/
              /*printf("\tpop\t%c\n", p->opr.op[0]->id.i + 'a');*/
              break;

            case UMINUS:
              /*ex(p->opr.op[0]);*/
              /*printf("\tneg\n");*/
              break;

            default:
              /*ex(p->opr.op[0]);*/
              /*ex(p->opr.op[1]);*/

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
