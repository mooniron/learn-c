/**************************************************************
* Name     :  ex3-7-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#include <string.h>

/*
    trim: remove trailing blanks, tabs, newlines,
*/
int trim(char s[]) {
    int n;

    for (n = strlen(s) - 1; n >= 0; n--) {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n') {
            break;
            }
        }
    s[n+1] = '\0';

    return n;
    }
