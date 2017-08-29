/**************************************************************
* Name     :  ex5-3-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
example: character pointer
    strcpy(s, t): copy t string to s tring.

*/

#include <stdio.h>

/*  strcpya: copy t to s, array subscript version  */
void strcpya(char *s, char *t) {
    int i;

    /*  s[i] == *(s + i); s == &s[0], s[0] != s;  */
    for (i = 0; (s[i] = t[i]) != '\0'; i++) {
        ;
        }
    }

/*  strcpyp1: point version 1  */
void strcpyp1(char *s, char *t) {

    while ((*s = *t) != '\0') {
        s++;
        t++;
        }
    }

/*  pointer version: no '\0'  */
void strcpyp2(char *s, char *t) {
    /*  '\0' == 0  */
    //while (*s++ = *t++){
    while ((*s++ = *t++) != '\0') {
    ;
        }
    }

/*  strcmp: return < 0 if s<t, 0 if s==t, >0 if s>t  */
int strcmp(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++) {
        if (s[i]  == '\0') {
            return 0;
            }
        }
    return s[i] - t[i];
    }

/*  strcmpp: pointer version  */
int strcmpp(char *s, char *t) {

    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
            }
        }
    return *s - *t;
    }

/*  main function  */
int main(void) {
    char *s;
    char *t;

    char sa[] = "stack dump";
    char ta[] = "stack dump";

    s = sa;
    t = ta;
    strcpyp1(s, t);
    //t[0] = t[1];
    s[0] = s[1];

    //printf ("%s\t", t);
    printf ("%s\n", s);
    printf ("%d\n", strcmpp(sa, ta));
    }
