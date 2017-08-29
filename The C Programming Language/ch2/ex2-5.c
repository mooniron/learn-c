/**************************************************************
* Name     :  ex2-5.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月24日
**************************************************************/

/*  any: return the location in s1 of any character in s2  ;
    if not find, return -1  */

#include <stdio.h>
#define MAXCOL 1000

/*  any: return the location in s1 of any character in s2  ;
    if not find, return -1  */
int any(char s1[], char s2[]) {
    int i, j;
    // the index of the find character.
    int index = -1;
    for (i = 0; s2[i] != '\0'; i++) {
        for (j = 0; s1[j] != '\0'; j++) {
            if (s1[j] == s2[i]) {
                index = j;
                break;
                }
            }
        if (index > -1) {
            break;
            }
        }
    return index;
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


/*  main function  */
int main() {
    int i;
    int index;
    char s1[MAXCOL];
    char s2[MAXCOL];

    //  get s1
    getstring(s1, MAXCOL);
    for (i = 0; i < 3; i++) {

        //  get s2
        getstring(s2, MAXCOL);
        index = any(s1, s2);
        if (index > -1){
            printf ("the location is %d.\n", index);
            }
        else {
            printf ("not find any.\n");
            }
        }
    }
