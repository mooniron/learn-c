/**************************************************************
* Name     :  ex4-12-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月3日
**************************************************************/

/*
exercise 4-12:
    reverse: recursive version
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[], int i, int j) {
    char temp;
    if (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
        reverse(s, i, j);
        }
    }

int main() {
    char s[] = "i love program";

    printf ("%s\n", s);
    reverse(s, 0, strlen(s) - 1);
    printf ("%s\n", s);
    }
