/**************************************************************
* Name     :  ex5-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercisse 5-3:
    strcat(s, t): add t to end of s, pointer verion
*/

#include <stdio.h>

/*  strcat(s, t): add t to end of s, pointer verion  */
void strcat(char *s, char *t) {
    /*  access to end of s '\0'  */
    while (*s != '\0') {
        s++;
        }
    /*  while ((*s++ = *t++) != '\0') {  */
    while ((*s = *t) != '\0') {
        s++;
        t++;
        }
    }

int main(void) {
    char s[] = "helllo, world.\t", t[] = "i love program\n";

    strcat(s, t);
    printf ("%s", &s[0]);
    }
