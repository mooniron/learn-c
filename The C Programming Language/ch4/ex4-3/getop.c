#include <stdio.h>
#include <ctype.h>
#include "calc.h"


/*  getop: get next character or numeric operand  */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
        }
    s[1] = '\0';
    /*  '.' : fractinal number; '-' : negative number  */
    if (!isdigit(c) && c !='.' && c != '-') {
        /*  not a number, return it, left the getop function  */
        return c;
        }
    i = 0;

    if (c == '-') {
        /*  '-' : substract notation , return it  */
        if (!isdigit(s[++i] = c = getch()) && c != '.') {
            if (c != EOF) {
                ungetch(c);
                }
            return s[0];
            }
        /*else {
            printf ("c is %c\n", c);
            }*/
        }

    if (isdigit(c)) {
        /*  collect integer part*/
        while (isdigit(s[++i] = c = getch())) {
            ;
            }
        }
    if (c == '.') {
        /*  collect fraction part  */
        while (isdigit(s[++i] = c = getch())) {
            ;
            }
        }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
        }
    return NUMBER;
    }

