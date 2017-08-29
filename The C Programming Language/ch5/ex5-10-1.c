/**************************************************************
* Name     :  ex5-10-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月11日
**************************************************************/

/*
exercise 5-10;
reverse polish calculator: command-line arguments verssion
    expr 2 3 4 + *
    -->  2 * (3 + 4)
*/

/*
    reverse Polish notation calculator: +, -, *, /, %, and negative

    infix expresion: (1 - 2) * (4 + 5) / (-2);
    revere Polish notation: 1 2 - 4 5 + * -2 /;

    outline:
    while (next operator or operand is not end-of-file indicator)
        if (number)
            push it
        else if (operator)
            pop operands
            do operation
            push result
        else if (newline)
            pop and print top of stack
        else
            error
*/

#include <stdio.h>
/*  for atof()  */
#include <stdlib.h>
/*  max size of operand or operator  */
#define MAXOF 100
/*  signal that a number was found  */
#define NUMBER '0'

int getop(char *);
void push(double);
double pop(void);

/*
reverse Polish calculator;
argc: count of command-line arguments, argv: a pointer array of arguments
*/
int main(int argc, char *argv[]) {
    int type;
    double op2;
    //  variable for mod1 % mod2
    int mod1, mod2;

    while (--argc > 0) {
        type = getop(*++argv);

        switch (type) {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            /*  case '*': escape character for shell, input '\*'  */
            case 'x':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0) {
                    push(pop() / op2);
                    }
                else {
                    printf ("error: zero division\n");
                    }
                break;
            case '%':
                op2 = pop();
                /*  mod2: integer; op2: double;  */
                mod2 = op2;
                mod1 = pop();
                if (op2 != 0) {
                    push(mod1 % mod2);
                    }
                else {
                    printf ("error: zero division\n");
                    }
                break;
            default:
                printf ("error: unknown command %s\n", *argv);
                argc = 0;
                break;
            }   //end switch(type)
        }   //end while (--argc > 0)

    printf("the results is: %f\n", pop());

    return 0;
    }

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

#include <ctype.h>


/*  getop: get next character or numeric operand  */
int getop(char *s) {
    int c;

    c = *s;
    /*  '.' : fractinal number; '-' : negative number  */
    if (!isdigit(c) && c !='.' && c != '-') {
        /*  not a number, return it, left the getop function  */
        return *s;
        }

    if (c == '-') {
        /*  '-' : substract notation , return it  */
        if (!isdigit(c = *++s) && c != '.') {
            return s[0];
            }
        }

    if (isdigit(c)) {
        /*  collect integer part*/
        return NUMBER;
        }
    if (c == '.') {
        /*  collect fraction part  */
        if (!isdigit(c = *++s)) {
            return *--s;
            }
        else {
            return NUMBER;
            }
        }
    *s = '\0';

    return NUMBER;
    }

#define BUFSIZE 100
/*  buffer for ungetch  */
char buf[BUFSIZE];
/*  next free position in buf  */
int bufp = 0;

/*  get a (possibly pushed back) character  */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
    }

/*  push character back on input  */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf ("ungetch: too many characters\n");
        }
    else {
        buf[bufp++] = c;
        }
    }
