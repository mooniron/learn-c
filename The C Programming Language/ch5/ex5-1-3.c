/**************************************************************
* Name     :  ex5-1-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  e2017年3月6日
**************************************************************/

/*
example: pointer function
    getint: get next integer from input into *pn.
    if is not a integer, return 0;
    if is EOF, return EOF.
    bug: treat a + or - not followed by a digit as a balid representation of zero.
*/

#include <stdio.h>

/*  size of array store integers  */
#define SIZE  100

int main(void) {
    int n, i, array[SIZE], getint(int *);

    for (n = 0; n < SIZE && (i = getint(&array[n])) != EOF;) {

        if (i != 0) {
            printf ("array[%d] = %d\n", n, array[n]);
            n++;
            }
        }
    }

#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, sign;

    /*  skip white space  */
    while (isspace(c = getch())) {
        ;
        }

    /*  it is not a number, return 0  */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        //ungetch(c);
        return 0;
        }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
        }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
        }
    /*  return EOF  */
    return c;
    }

int last;
bool getflag = true;

int getch(void) {
    /*  if have store a character in last, return it and set getflag false  */
    if (getflag) {
        getflag = false;
        return last;
        }
    /*  no character in last, return getchar()  */
    else {
        return getchar();
        }
    }

void ungetch(int c) {
    if (getflag) {
        printf ("there is already an integer, too many to push back\n");
        }
    else {
        getflag = true;
        last = c;
        }
    }
