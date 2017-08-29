/**************************************************************
* Name     :  ex5-4-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercisse 5-4:
    strend: return 1 if string t occurs at the end of s, zero otherwise.
*/

#include <stdio.h>

/*  strend: return 1 if string t occiurs at the end of s, zero otherwise  */
int strend(char *s, char *t) {
    /*  t is null  */
    if (*t == '\0') {
        return 0;
        }
    /*  *t is the first element  */
    while (*s != *t) {
        if (*s == '\0') {
            return 0;
            }
        s++;
        }
    while (*++s == *++t && *s !='\0') {
        ;
        }
    if (*s == '\0' && *t == '\0') {
        return 1;
        }
    return 0;
    }

int main(void) {
    int i;
    char s[] = "hool", t[] = "l";

    i = strend(s, t);
    printf ("%d\n", i);
    }
