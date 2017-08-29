/**************************************************************
* Name     :  ex4-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
/*  maximum input line length  */
#define MAXCOL 1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

/*  pattern to search for  */
char pattern[] = "ould";

/*  find all lines matching pattern  */
int main() {
    char line[MAXCOL];
    int found = 0;
    int index;
    while (getline(line, MAXCOL) > 0) {
        if ((index = strindex(line, pattern)) >= 0) {
            printf ("the rightmost index is %d\n", index);
            found++;
            }
        else {
            printf ("NOT FOUND\n");
            }
        }
    return found;
    }

/*  getline: getline into s, return length  */
int getline(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
        }
    if (c == '\n') {
        s[i++] = c;
        }
    s[i] = '\0';
    return i;
    }

/*  strindex: return rightmost index of t in s,
    return -1 if none  */
int strindex(char s[], char t[]) {
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
            ;
            }
        if (k > 0 && t[k] == '\0') {
            return (j-1);
            }
        }
    return -1;
    }
