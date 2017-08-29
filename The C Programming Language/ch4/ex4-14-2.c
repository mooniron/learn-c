/**************************************************************
* Name     :  ex4-14-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月5日
**************************************************************/

/*
example: macro define
*/

#include <stdio.h>
/*  wrong: square(5 + 1) == 5 + 1 * 5 + 1  */
#define square(x) x * x
#define max(a, b) (a > b) ? a : b
/*  #expr == "expr"  */
#define dprint(expr) printf(#expr " = %g\n", expr)
/*  front ## back == frontback  */
#define paste(front, back) front ## back
int main() {
    int z = 3;
    int a = 3;
    int b = 6;

    printf ("a = %d, b = %d\n", a, b);
    /*  wrong: printf argument calculate order is random  */
    printf ("a = %d, b = %d, max(a++, b++) is %d\n", a, b, max(a++, b++));
    printf ("a = %d, b = %d\n", a, b);
    printf ("%d\n",square(z + 1));
    dprint(b/a);
    }

arcane
