/**************************************************************
* Name     :  ex7-5-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
exercise 7-5:
    rewrite the postfix calculator of chapter 4 to use scanf and/or sscanf to do the input and
    number conversion.

scanf:
    1.  scanf skip blanks and '\n';
    2.  if input EOF, scanf return EOF;
    3.  scanf("%c", &c) will not skip blank spaces and '\n';

outline:
    1.  scanf oprands double, return NUMBER;
    2.  if input EOF, return EOF;
    3.  scanf operator, return operator;
    4.  use '=' as output result operator instead of '\n'
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

int getop(double *);
void push(double);
double pop(void);

/*  reverse Polish calculator  */
int main(void) {
    int type;
    double op, op2;
    //  variable for mod1 % mod2
    int mod1, mod2;
    //char s[MAXOF];

    op = op2 = 0.0;

    while ((type = getop(&op)) != EOF) {
        switch (type) {
            case NUMBER:
                push(op);
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
            /*  scanf skip blanks and '\n'  */
            //case '\n':
            case '=':
                printf ("\t%0.8g\n", pop());
                break;
            default:
                printf ("error: unknown command %c\n", type);
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
int getop(double *op) {
    int i;
    char c;

    i = 0;
    // operands
    if ((i = scanf("%lf ", op)) == 1) {
        return NUMBER;
        }
    // EOF
    else if (i == EOF) {
        return i;
        }
    // operator
    else {
        //printf("i = %d, op = %lf\n", i, *op);
        // scanf skip blanks and '\n'
        scanf("%c", &c);
        return c;
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
