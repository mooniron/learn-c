/**************************************************************
* Name     :  ex4-3-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月1日
**************************************************************/

/*
    reverse Polish notation calculator: +, -, *, /,

    infix expresion: (1 - 2) * (4 + 5);
    revere Polish notation: 1 2 - 4 5 + *;

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

int getop(char []);
void push(double);
double pop(void);

/*  reverse Polish calculator  */
int main(void) {
    int type;
    double op2;
    char s[MAXOF];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                    }
                else {
                    printf ("error: zero division\n");
                    }
                break;
            case '\n':
                printf ("\t%0.8g\n", pop());
                break;
            default:
                printf ("error: unknown command %s\n", s);
                break;
            }
        }
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

int getch(void);
void ungetch(int);

/*  getop: get next character or numeric operand  */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
        }
    s[1] = '\0';
    if (!isdigit(c) && c !='.') {
        /*  not a number, return it, left the getop function  */
        return c;
        }
    i = 0;

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
