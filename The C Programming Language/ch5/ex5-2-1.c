/**************************************************************
* Name     :  ex5-2-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  e2017年3月6日
**************************************************************/

/*
exercise: 5-2:
    getfloat, the floating-point analog of getfloat.
*/

#include <stdio.h>

/*  size of array store integers  */
#define SIZE  100

int main(void) {
    int n, i, getfloat(float *);
    /*  34533.00 / 100.0 != 345.33  */
    float array[100];

    for (n = 0; n < SIZE && (i = getfloat(&array[n])) != EOF;) {

        if (i != 0) {
            printf ("array[%d] = %f\n", n, array[n]);
            n++;
            }
        }
    }

#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
    int c;
    float sign, pow = 1.0;

    /*  skip white space  */
    while (isspace(c = getch())) {
        ;
        }

    /*  it is not a number, return 0. + , - for sign, '.' for float  */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        //ungetch(c);
        return 0;
        }

    sign = (c == '-') ? -1.0 : 1.0;
    if (c == '+' || c == '-') {
        c = getch();
        /*  next char after '-' or '+' is not a integer, push it back  */
        if (!isdigit(c)) {
            ungetch(c);
            return 0;
            }
        }
    /*  integer part  */
    for (*pn = 0.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        }

    /*  fraction part  */
    if (c == '.') {
        if (!isdigit(c = getch())) {
            ungetch(c);
            return 0;
            }
        else {
            for (pow = 1.0; isdigit(c); c = getch()) {
                *pn = 10.0 * *pn + (c - '0');
                pow *= 10.0;
                }
            }
        }
    /*  total result  */
    *pn = sign * (*pn) / pow;
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
