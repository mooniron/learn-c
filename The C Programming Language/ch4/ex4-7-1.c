/**************************************************************
* Name     :  ex4-7-1.c
* Author   :  Bronze Lee
* Version  :  0.2 pop, push
* Date     :  2017年3月1日
**************************************************************/

/*
exercise 4-7:
    ungets(char s[]): push back string s.
*/
/*
exercise 4-6:
    add commands for handling variables.
    add a bariable for the most recently printed value.

    dealvar:
        if current variable exist in varname, push relevant varvalue, return the index.
        else pop the top item, store it in the last index varvalue  , return last
*/

/*
exercise 4-5:
    add access to library functions like sin, exp, and pow.
*/

/*
exercise 4-4:
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
/*  for sin, exp, pow  */
#include <math.h>
/*  max size of operand or operator  */
#define MAXOF 100
/*  signal that a number was found  */
#define NUMBER '0'
/*  sin function flag  */
#define SIN '1'
/*  exp function flag  */
#define EXP '2'
/*  pow function flag  */
#define POW '3'
/*  variable flag  for 'a', 'b'... 'z'  */
#define VAR '4'
/*  variable for most recently printed value  */
#define RES '5'

int getop(char []);
void push(double);
double pop(void);
void showtop(void);
void duplicate(void);
void swapitem(void);
void clearstack(void);
int dealvar(char s[]);


/*  reverse Polish calculator  */
int main(void) {
    int type;
    double op2;
    /*  the result of a line  */
    double res = 0.0;
    //  variable for mod1 % mod2
    int mod1, mod2;
    /*  the variable flag and value  */
    //int varflag = 0;
    //int vartype = 0;

    char s[MAXOF];
    //char varname[MAXOF];
    //double varvalue[MAXOF];

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
            case SIN:
                push(sin(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case VAR:
                dealvar(s);
                break;
            case RES:
                push(res);
                break;
            case '?':
                //  print the top item of stack
                showtop();
                break;
            case '#':
                //  dulplicate the top item of stack
                duplicate();
                break;
            case '~':
                //  swap the top two item of stack
                swapitem();
                break;
            case '|':
                //  clear stack
                clearstack();
                break;
            case '\n':
                //varflag = 0;
                res = pop();
                printf ("\t%0.8g\n", res);
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
        double item = pop();
        push(item);
        push(item);
        }
    else {
        printf ("error: stack full.the top element of stack is %g\n", val[MAXVAL-1]);
        }
    }

/*  swapitem: swap the top two item of stack  */
void swapitem(void) {
    if (sp > 1) {
        double item1 = pop();
        double item2 = pop();
        push(item1);
        push(item2);
        }
    else {
        printf ("less then two item in stack\n");
        }
    }

/*  clearstack: clear the stack  */
void clearstack(void) {
    sp = 0;
    //printf ("the stack is cleared");
    }

/*  maximum number of variable  */
#define MAXVAR 100
/*  the last index of var[]  */
int last = 0;
/*  varialble name  */
char varname[MAXVAR];
/*  variable value  */
double varvalue[MAXVAR];

/*  dealvar: deal with variable  */
int dealvar(char s[]) {
    int i, j;
    /*  if current variable exist in varname, push relevant varvalue, return the index.
        else pop the top item, store it in the last index varvalue  , return last  */
    for (i = 0; s[i] != '\0'; i++) {
        for (j = 0; j < last; j++) {
            if (varname[j] == s[i]) {
                push(varvalue[j]);
                return j;
                }
            }
        }
    /*  not find the var, assign last variable  */
    varvalue[last] = pop();
    push(varvalue[last]);
    varname[last] = s[0];
    varname[++last] = '\0';
    return last - 1;
    }


#include <ctype.h>

int getch(void);
void ungetch(int);
void ungets(char []);

/*  getop: get next character or numeric operand  */
int getop(char s[]) {
    int i, c;
    int nx1, nx2;

    /*  ignore the blanks  */
    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
        }
    s[1] = '\0';
    /*  '.' : fractinal number; '-' : negative number  */
    if (!isdigit(c) && c !='.' && c != '-' && (c < 'a' || c > 'z')) {
        /*  not a number, return it, left the getop function  */
        return c;
        }

    i = 0;
   /*  sin function, return SIN  */
    if (c == 's') {
        nx1 = getch(); nx2 = getch();
        if (nx1 == 'i' && nx2 == 'n') {
            s[++i] = nx1;
            s[++i] = nx2;
            s[++i] = '\0';
            return SIN;
            }
        else {
            if (nx2 != EOF && nx1 != EOF) {
                ungetch(nx2);
                ungetch(nx1);
                }
            //return c;
            }
        }
    /*  exp function, return EXP  */
    if (c == 'e') {
        nx1 = getch(); nx2 = getch();
        if (nx1 == 'x' && nx2 == 'p') {
            s[++i] = nx1;
            s[++i] = nx2;
            s[++i] = '\0';
            return EXP;
            }
        else {
            if (nx2 != EOF && nx1 != EOF) {
                ungetch(nx2);
                ungetch(nx1);
                }
            //return c;
            }
        }
    /*  pow function, return POW  */
    if (c == 'p') {
        nx1 = getch(); nx2 = getch();
        if (nx1 == 'o' && nx2 == 'w') {
            s[++i] = nx1;
            s[++i] = nx2;
            s[++i] = '\0';
            return POW;
            }
        else {
            if (nx2 != EOF && nx1 != EOF) {
                ungetch(nx2);
                ungetch(nx1);
                }
            //return c;
            }
        }
        /*  res variable for last printed value, return RES  */
        if (c == 'r') {
            s[i++] = getch(); s[i++] = getch();
            if (s[1] == 'e' && s[2] == 's') {
                s[++i] = '\0';
                return RES;
                }
            else {
                if (s[1] != EOF && s[2] != EOF) {
                    s[0] = s[1];
                    s[1] = s[2];
                    s[2] = '\0';
                    ungets(s);
                    }
                //return c;
                }
        }
    /*  a-z for variable name, return VAR  */
    if (c >= 'a' && c <= 'z') {
        return VAR;
        }

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

    return -1;
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

void ungets(char s[]) {
    int i = 0;
    int len;

    for (i = 0; s[i] != '\0'; i++) {
        ;
        }
    len = i;

    for (i = len; i >= 0; i--) {
        ungetch(s[i]);
        }
    }
