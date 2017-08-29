/**************************************************************
* Name     :  ex4-10-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月1日
**************************************************************/

/*
exercise 4-10:
    use getline to read an entire input line
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
/*  max line column  */
#define MAXCOL 1000

int getop(char [], char []);
void push(double);
double pop(void);
int getline(char line[], int lim);

/*  reverse Polish calculator  */
int main(void) {
    int type;
    double op2;
    //  variable for mod1 % mod2
    int mod1, mod2;
    char line[MAXOF];
    char op[MAXOF];

    extern int inx;

    while (getline(line, MAXCOL) > 0) {
        /*  initial the line[inx]  */
        inx = 0;

        while ((type = getop(line, op)) != '\0') {
        switch (type) {
            case NUMBER:
                push(atof(op));
                //printf ("s is %f\n", atof(op));
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
                printf ("error: unknown command %s\n", op);
                break;
            }
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
/*  the index of input line  */
int inx = 0;

/*  getop: get next character or numeric operand  */
int getop(char s[], char op[]) {
    int i, c;
    //  store the next item in s[]
    //int temp;

    while ((op[0] = s[inx]) == ' ' || s[inx] == '\t') {
        inx++;
        }
    c = s[inx++];
    op[1] = '\0';
    /*  '.' : fractinal number; '-' : negative number  */
    if (!isdigit(c) && c !='.' && c != '-') {
        /*  not a number, return it, left the getop function  */
        return c;
        }
    i = 0;

    if (c == '-') {
        /*  '-' : substract notation , return it  */
        if (!isdigit(s[inx]) && s[inx] != '.') {

            return c;
            }
        else {
            op[i++] = c;
            c = s[inx++];
            }
        }

    if (isdigit(c)) {
        op[i++] = c;
        /*  collect integer part*/
        while (isdigit(s[inx])) {
            op[i++] = s[inx];
            inx++;
            }
        }
    if (s[inx] == '.') {
        op[i++] = s[inx++];
        /*  collect fraction part  */
        while (isdigit(s[inx])) {
            op[i++] = s[inx];
            inx++;
            }
        }
    op[i] = '\0';
    return NUMBER;
    }

/* getline : resd a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    {
        s[i] = c;
        }
    if (c == '\n') {
        s[i] = c;
        ++i;
        }

    s[i] = '\0';
    return i;
}
