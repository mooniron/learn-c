/**************************************************************
* Name     :  ex3-3-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*  atoi: convert s to integer, version 2  */
int atoi(char s[]) {
    int i, n, sign;
    //  skip white space
    for (i = 0; isspace(s[i]); i++) {
        ;
        }
    sign = (s[i] == '-') ? -1 : 1;
    // skip sign
    if (s[i] == '+' || s[i] == '-') {
        i++;
        }
    for (n = 0; isdigit(s[i]); i++) {
        n = 10 * n + (s[i] - '0');
        }
    return sign * n;
    }

/*  shell sort: sort v[0] ... v[n-1] into increasing order  */
void shellsort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
                }
            }
        }
    }

/*  reverse: reversse string s in place  */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        }
    }
