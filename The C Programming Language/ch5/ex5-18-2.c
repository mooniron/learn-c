/**************************************************************
* Name     :  ex5-18-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月17日
**************************************************************/

/*
example: complex declaration
dcl: convert a C declaration into a word description.
    char **argv
        argv: pointer to pointer to char
    int (*daytab)[13]
        daytab: pointer to array[13] of int
    int *daytab[13]
        daytab: array[13] of pointer to int
    void *comp()
        comp: function returning pointer to void
    void (*comp)()
        comp: pointer to function returning void
    char (*(*x())[])()
        x: function returning pointer to array[] of pointer to function returning char
    char (*(*x[3])())[5]
        x: array[3] of pointer to function returning pointer to array[5] of char

    dcl: optional *'s direct-dcl direct-dcl name (dcl) direct-dcl() direct-dcl[optional size]

dirdcl: direct-dcl
recursive-descent parser

undcl:
    convert a word description like
    "x is a function returning a pointer to an array of pointers to functions returning char, "
    which we will express as :
    x () * [] * () char
    to char (*(*x())[])()

*/



#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
int undcl(void);
int gettoken(void);

/*  type of last token  */
int tokentype;
/*  last token string  */
char token[MAXTOKEN];
/*identifier name  */
char name[MAXTOKEN];
/*  data type = char, int, etc  */
char datatype[MAXTOKEN];
char out[1000];

/*  convert declaration to words  */
int main(void) {

    //undcl();

    while (gettoken() != EOF) {
        /*  1st token is the datatype  */
        strcpy(datatype, token);
        out[0] = '\0';
        /*  parse rest of line  */
        dcl();

        if (tokentype != '\n') {
            printf("syntax error\n");
            }   //end if

        printf("%s: %s %s\n", name, out, datatype);
        }   //end while

    return 0;
    }   //end function main


/*  return next token  */
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    /*  skip blanks  */
    while ((c = getch()) == ' ' || c == '\t') {
        ;
        }   //end while

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
            }
        else {
            ungetch(c);
            return tokentype = '(';
            }   //end if ((c =
        }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) {
            ;
            }   //end for
        *p = '\0';
        return tokentype = BRACKETS;
        }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
            }   //end for
        *p++ = '\0';
        ungetch(c);
        return tokentype = NAME;
        }
    else {
        return tokentype = c;
        }   //end if

    }   //end function gettoken

/*  getch block  */
#define GETSIZE 1000
static int sp;
static char getbuf[GETSIZE];

/*  getch: return getbuf[--sp] if sp > 0, else return getchar  */
int getch(void) {
    if (sp > 0) {
        return getbuf[--sp];
        }
    else {
        return getchar();
        }   //end if
    }   //end function getch

/*  ungetch: store c in getbuf  */
void ungetch(int c) {
    if (sp < GETSIZE) {
        getbuf[sp++] = c;
        }
    else {
        printf("no space for ungetch\n");
        }   //end if
    }   //end functio ungetch



/*  dcl block  */
/*  dcl: parse a declarator  */
void dcl(void) {
    int ns;

    /*  count *'s  */
    for (ns = 0; gettoken() == '*';) {
        ns++;
        }   //end for (ns =

    dirdcl();

    while (ns-- > 0) {
        strcat(out, " pointer to");
        }   //end while

    }   //end function dcl


/*  dirdcl: parse a direct declarator  */
void dirdcl(void) {
    int type;

    /*  ( dcl )  */
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            }   //end if
        }
    /*  variable name  */
    else if (tokentype == NAME) {
        strcpy(name, token);
        }
    else {
        printf("error: expected name or (dcl)\n");
        }   //end if

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
            }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
            }   //end if
        }   //end while

    }   //end function dirdcl



/*  undcl block  */
/*  undcl: convert word descriptions to declarations  */
int undcl(void) {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
                }
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
                }
            else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
                }
            else {
                printf("invalid input at %s\n", token);
                }   //end if
            }   //end while
        }   //end while

    return 0;
    }   //end function undcl
