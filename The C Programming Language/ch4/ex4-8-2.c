/**************************************************************
* Name     :  ex4-8-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月3日
**************************************************************/

/*
exercise 4-8;
    getch, ungetch only one character.
    this version can't handle EOF.
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

int getop(char []);
void push(double);
double pop(void);

/*  reverse Polish calculator  */
int main(void) {
    int type;
    double op2;
    //  variable for mod1 % mod2
    int mod1, mod2;
    char s[MAXOF];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                //printf ("s is %f\n", atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                //printf ("op2 is %f\n", op2);
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
            case '%':
                /*  pop stack to op2  */
                op2 = pop();
                /*  convert op2 to integer  */
                mod2 = op2;
                mod1 = pop();
                if (mod2 != 0) {
                    push(mod1 % mod2);
                    }
                else {
                    if (op2 != 0.0) {
                        printf ("abs(operand2) < 1, convert it to 0\n");
                        }
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
        ungetch(EOF);
        }
    return NUMBER;
    }

int buf = EOF; /* buffer for ungetch */

int getch(void) /* get a (possibly pushed back) character */
{
  int temp;

  if (buf != EOF) {
    temp = buf;
    buf = EOF;
  } else {
    temp = getchar();
  }
  return temp;
}

void ungetch(int c) /* push character back on input */
{
  if(buf != EOF)
    printf("ungetch: too many characters\n");
  else
    buf = c;
}
