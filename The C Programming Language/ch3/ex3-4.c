/**************************************************************
* Name     :  ex3-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

/*  itoa: convert n to characters in s  */
void itoa(int n, char s[]) {
    int i, sign;

    /*  record sign  */
    if ((sign = n) < 0) {
        /*  make n positive  */
        n = -n;
        }
    i = 0;
    /*  generate digits in reverse order  */
    do {
        s[i++] = n % 10 + '0';
        }
    /*  delete the last number  */
    while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
        }
    s[i] = '\0';
    reverse(s);
    }

/*  itoac: correct itoa to convert langest negative number correctly, -power(2, wordsize-1)*/
void itoac(int n, char s[]) {
    int i, sign;

    i = 0;
    sign = n;

    do {
        s[i++] = abs(n % 10) + '0';
        }
    while (n /= 10);
    if (sign < 0) {
        s[i++] = '-';
        }
    s[i] = '\0';
    reverse(s);
    }

/*  reverse: reverse string s  */
void reverse(char s[]) {
    int i, j, c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        }
    }

int main() {
    char buffer[20];

    printf ("INT_MIN : %d\n", INT_MIN);
    itoac(INT_MIN, buffer);
    printf ("INT_MIN char string buffer : %s\n", buffer);
    itoa(INT_MIN, buffer);
    printf ("INT_MIN char string buffer : %s\n", buffer);

    return 0;
    }
