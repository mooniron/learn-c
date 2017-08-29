/**************************************************************
* Name     :  ex1-23-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月5日
**************************************************************/


/*
this version can handle the escape sequences properly.
*/


/*
exercise 1-23:
    write a program to remove all comments from a c program. don't forget to handle quoted
strings and character constants properly, c comments don't nest.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCOL 1024
#define MAXROW 1024

int getch(void);
int ungetch(int);

int main() {
    int c, ic, iq, in;
    /*  quote and comment flags  */
    int escape, quote, comment, quotecom;
    char comments[MAXCOL], quotes[MAXCOL], *temp, *normal;

    normal = (char *) malloc(MAXROW * MAXCOL);
    temp = normal;
    if (normal == NULL) {
        fprintf(stderr, "no enough buffer space\n");
        return -1;
        }

    c = ic = iq = in = 0;
    escape = quote = comment = quotecom = 0;

    while ((c = getch()) != EOF) {
        // escape flag
        if (c == '\\') {
            escape = 1;
            *normal++ = c;
            continue;
            }
        if (escape == 1) {
            escape = 0;
            *normal++ = c;
            continue;
            }

        // quote flag
        if (c == '"' && comment == 0) {
            if (quotecom == 1) {
                comments[ic++] = c;
                //comments[ic] = '\0';
                strcpy(normal, comments);
                normal += ic;
                ic = 0;
                iq = 0;
                quotecom = 0;
                }
            else if (quotecom == -1) {
                quotes[iq++] = c;
                strcpy(normal, comments);
                normal += ic;
                strcpy(normal, quotes);
                normal += iq;
                ic = 0;
                iq = 0;
                quotecom = 0;
                }
            else if (quote == 1) {
                *normal++ = c;
                quote = 0;
                }
            else {
                *normal++ = c;
                quote = 1;
                }
            continue;
            }
        else if (c == '/' && comment == 0) {
            if ((c = getch()) != '*') {
                *normal++ = '/';
                ungetch(c);
                continue;
                }
            // is a comment flag
            comments[ic++] = '/';
            comments[ic++] = '*';
            if (quote == 1) {
                quote = 0;
                quotecom = 1;
                }
            else{
                comment = 1;
                }
            continue;
            }   //end if c = /
        else if (c == '*' && (comment == 1 || quotecom == 1)) {
            if ((c = getch()) != '/') {
                comments[ic++] = '*';
                ungetch(c);
                continue;
                }
            // is an comment end flag
            comments[ic++] = '*';
            comments[ic++] = '/';
            if (comment == 1) {
                comment = 0;
                ic = 0;
                iq = 0;
                }
            else if (quotecom == 1) {
                quotecom = -1;
                }
            continue;
            }   //end if c == *
        else if (comment == 1 || quotecom == 1) {
            comments[ic++] = c;
            }
        else if (quotecom == -1) {
            quotes[iq++] = c;
            }
        else {
            *normal++ = c;
            }
        }   // end while

    if (quotecom == -1) {
        strcpy(normal, quotes);
        normal += iq;
        }
    else if (comment == 1 || quotecom == 1) {
        strcpy(normal, comments);
        normal += ic;
        }

    ic = iq = 0;
    *normal = '\0';
    normal = temp;
    printf("\n\n%s\n", normal);

    return 0;
    }   //end function main


/*  getch block  */
static int getflag = 0;
static int ch = 0;

int getch() {
    if (getflag > 0) {
        getflag = 0;
        return ch;
        }
    else {
        return getchar();
        }
    }   //end function getch

int ungetch(int c) {
    if (getflag == 0) {
        ch = c;
        getflag = 1;
        return ch;
        }
    else {
        return -1;
        }
    }   //end function ungetch
