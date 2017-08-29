/**************************************************************
* Name     :  ex2-10.c
* Author   :  Bronze Lee
* Version  :  0.1 conditional expression
* Date     :  2017年2月24日
**************************************************************/

#include <stdio.h>
#define MAXCOL 1000

/*  lower: invert upper case to lower case  */
void lower(char s[]) {
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? (s[i] + 'a' - 'A') : s[i] ;
        }
    s[i] = '\0';
    }

/* getline : resd a line into s, return length */
int getstring(char line[], int slim) {
    int i, c;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < slim - 1 ) {
            line[i] = c;
            }
        }

    if (i < slim - 1) {
        line[i] = '\0';
        }
    else {
        line[slim - 1] = '\0';
        }
    return i;
    }


int main() {
    char line[MAXCOL];

    while (getstring(line, MAXCOL) > 0) {
        lower(line);
        printf ("%s\n", line);
        }
    }
