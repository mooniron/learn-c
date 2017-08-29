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

/*  itoa: convert n into a base b character string in s  */
void itoa(int n, char s[], int b) {
    int i, sign;

    i = 0;
    sign = n;
    if (b > 0) {
        do {
            s[i++] = abs(n % b) + '0';
            }
        while (n /= b);
        if (sign < 0) {
            s[i++] = '-';
            }
        s[i] = '\0';
        reverse(s);
        }
    else {
        printf ("ERROR, the base must be greater than zero\n");
        s[i] = '\0';
        }
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

    printf ("INT_MIN : %x\n", INT_MIN);
    itoa(INT_MIN, buffer, 16);
    printf ("INT_MIN char string buffer : %s\n", buffer);

    return 0;
    }
