/**************************************************************
* Name     :  ex4-4-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月1日
**************************************************************/

/*
    add showtop, duplicate, swapitem, clearstack.
    case ?: showtop;
    case #: duplicate;
    case ~: swapitem;
    case |: clearstack;
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
void duplicate(void);


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
            case '?':
                //  print the top item of stack
                //showtop();
                break;
            case '#':
                //  dulplicate the top item of stack
                duplicate();
                break;
            case '~':
                //  swap the top two item of stack
                //swapitem();
                break;
            case '|':
                //  clear stack
                //clearstack();
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

/*  showtop: printf the top item of stack;  */
void showtop() {
    if (sp > 0) {
        printf ("the top item of stack is %0.8g\n", val[sp-1]);
        }
    else {
        printf ("the stack is empty\n");
        }
    }

/*  duplicate: duplicate the top of stack, and print it  */
void duplicate(void) {
    if (sp < MAXVAL) {
        val[sp] = val[sp-1];
        sp++;
        }
    else {
        printf ("error: stack full.the top element of stack is %g\n", val[MAXVAL-1]);
        }
    }

/*  swapitem: swap the top two item of stack  */
void swapitem(void) {
    double temp;
    if (sp > 1) {
        temp = val[sp-2];
        val[sp-2] = val[sp-1];
        val[sp-1] = temp;
        }
    else {
        printf ("less then two item in stack\n");
        }
    }

/*  clearstack: clear the stack  */
void clearstack(void) {
    sp = 0;
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
