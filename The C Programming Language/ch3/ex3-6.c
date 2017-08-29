/**************************************************************
* Name     :  ex3-5.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

/*  itoa: convert n into a base b character string in s,
    if length of s < w, pad with blanks on the left  */
void itoa(int n, char s[], int w) {
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
    //  s length < w, insert blanks
    while (i < w) {
        s[i++] = ' ';
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
    int n = 1;
    char buffer[20];

    itoa(n, buffer, 4);
    printf ("%d char string buffer : %s\n", n, buffer);

    return 0;
    }
