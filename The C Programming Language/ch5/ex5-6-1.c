/**************************************************************
* Name     :  ex5-6-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercise 5-6: pointer version
    strlen:
    getline:
    atoi:
    itoa:
    reverse:
    strindex:
*/

#include <stdio.h>
#include <limits.h>


/*  strlen: get the length of a string  */
int strlen(char *s) {
    int n = 0;

    while (*s++ != '\0') {
        n++;
        }
    return n;
    }

/*  getline: get input line, pointer version, return its length  */
int getline(char *s) {
    int i, c;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        *s++ = c;
        }
    if (c == '\n') {
        *s++ = c;
        i++;
        }
    *s = '\0';

    return i;
    }

/*  atoi: convert a string to integer, return the integer, pointer version  */
int atoi(char *s) {
    int pn, sign;

    pn = 0;
    while (*s == ' ' || *s == '\t') {
        s++;
        }

    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' or *s == '-') {
        s++;
        }
    while (*s >= '0' && *s <= '9') {
        pn = 10 * pn + (*s - '0');
        s++;
        }
    return sign * pn;
    }

/*  reverse: reverse string s, pointer version  */
void reverse(char *s) {
    int len, temp;
    char *t;

    len = strlen(s);

    for (t = s + len - 1; s < t; s++, t--) {
        temp = *s;
        *s = *t;
        *t = temp;
        }
    }

/*  itoa: convert an interger to a string, return it  */
char *itoa(int n, char *s) {
    int i, j, sign;
    char *t = s;

    sign = n;

    do {
        /*  *s++ = abs(n % 10) + '0'  */
        if ((i = n % 10) < 0) {
            *s++ = -i + '0';
            j++;
            }
        else {
            *s++ = i + '0';
            j++;
            }
        }
        while (n /= 10);

    if (sign < 0) {
        *s++ = '-';
        j++;
        }
    *s = '\0';
    //reverse(t);
    //t = s - 2;
    reverse(t);
    return t;

    }

/*  strindex: return the index of char c in string s, or return -1 if not found  */
int strindex(char c, char *s) {
    int i = 0;

    while (*s != '\0') {
        if (*s == c) {
            return i;
            }
        i++;
        s++;
        }

    return -1;
    }

int main(void) {
    //char s[1];
    char *ing;
    int pn;

    getline(ing);
    pn = strindex('o', ing);
    printf ("the index is %d\n", pn);
    while (getline(ing) > 0) {

        pn = atoi(ing);
        printf ("pn = %d\n", pn);
        itoa(INT_MIN, ing);
        printf ("%s\n", ing);

        }

    }
