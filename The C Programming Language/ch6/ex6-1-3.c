/**************************************************************
* Name     :  ex6-1-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月16日
**************************************************************/


/*
example: arrays of structures
count C keywords:
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);

struct key {const char *word; int count;} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "else", 0,
    "float", 0,
    "for", 0,
    "if", 0,
    "int", 0,
    /* ... */
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0,
    };

//#define NKEYS (sizeof keytab / sizeof(struct key))
#define NKEYS (sizeof keytab / sizeof(keytab[0]))


/*  count C keywords  */
int main(void) {
    int n;
    char word[MAXWORD];

    n = 0;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
                }
            }
        }   //end while

    for (n = 0; (unsigned) n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
            }   //end if
        }   //end for

    return 0;
    }   //end function main


/*  binsearch: find word in tab[0]...tab[n-1] in increasing order  */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
            }
        else if (cond > 0) {
            low = mid + 1;
            }
        else {
            return mid;
            }   //end if
        }   //end while

    /*  not found  */
    return -1;
    }   //end function binsearch


/*  getword: get next word or character from input  */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    /*  skip spaces  */
    while (isspace(c = getch())) {
        ;
        }   //end while

    if (c != EOF) {
        *w++ = c;
        }   //end if
    /*  isalpha: identify letters  */
    if (!isalpha(c)) {
        *w = '\0';
        return c;
        }   //end if
    /*  isalnum: identify letters and digits  */
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
            }
        }   //end for
    *w = '\0';

    return word[0];
    }   //end function getword


/*  getch block  */
int ch;
int ungetflag = 0;

int getch(void) {
    if (ungetflag == 1) {
        ungetflag = 0;
        return ch;
        }
    else {
        return getchar();
        }
    }   //end function getch

void ungetch(int c) {
    if (ungetflag == 0) {
        ch = c;
        ungetflag = 1;
        }
    else {
        printf("error: there is already a character in stack\n");
        }
    }   //end function ungetch
