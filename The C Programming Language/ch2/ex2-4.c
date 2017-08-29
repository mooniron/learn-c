/**************************************************************
* Name     :  ex2-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月24日
**************************************************************/

/*  function : squeeze , delete all c from string s[] ;
    squeezearray: delete each character in s1 that matches any character in the string s2 ;
    */
#include <stdio.h>
#define MAXCOL 1000

/*  squeeze: delete all c from s  */
void squeeze(char s[], int c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
            }
        }
    s[j] = '\0';
    }

/*  strcat: concatenate t to end of s: s must be big enough  */
void strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    /*  find end of s  */
    while (s[i] != '\0') {
        i++;
        }
    /*  copy t to s end  */
    while ((s[i++] = t[j++]) != '\0') {
        ;
        }
    s[i] = '\0';
    }

/*  squeezearray: delete each character in s1 that matches any character in the string s2  */
void squeezearray(char s1[], char s2[]) {
    int i, j, k;

    //i = j = k = 0;
    /*  get each character in s2  */
    for (i = 0; s2[i] != '\0'; i++) {
        k = 0;
        for (j = 0; s1[j] != '\0'; j++) {
            if (s1[j] != s2[i]) {
                s1[k++] = s1[j];
                }
            }
        s1[k] = '\0';
        }
    }

/* getline : resd a line into s, return length */
int getline(char line[], int slim) {
    int i, c;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < slim - 1 ) {
            line[i] = c;
            }
        }
    if (c == '\n') {
        if (i < slim - 1) {
            line[i] = c;
            }
        i++;
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
    char s1[MAXCOL];
    char s2[MAXCOL];

    for (i = 0; i < 3; i++) {
        getline(s1, MAXCOL);
        //printf ("the orginal s1 is : %s\n", s1);
        getline(s2, MAXCOL);
        //printf ("s2 is : %s\n", s2);
        squeezearray(s1, s2);
        printf (" squeezearray s1[] from s2[].\n\n");
        printf ("%s", s1);
        }
    }
