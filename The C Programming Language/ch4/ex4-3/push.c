#include <stdio.h>
#include "calc.h"

/*  maximum depth of val stack  */
#define MAXVAL 100
/*  next free stack position  */
int sp = 0;
/*  value stack  */
double val[MAXVAL];

/*  push: push f onto value stack  */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
        }
    else {
        printf("error: stack full. can't push %g\n", f);
        }
    }

/*  pop: pop and return top value from stack  */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
        }
    else {
        printf("error: stack empty\n");
        return 0.0;
        }
    }

