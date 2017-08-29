/**************************************************************
* Name     :  ex5-5-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercisse 5-5:
    strcpy(s, t, n): copy the most first n characters of t to s.
    strcat(s, t, n): add the most first n characters of t to end of s.
    strcmp(s, t, n): get most first n characters of t compare to s.
*/

# include <stdio.h>


/*  strlen: get the length of a string  */
int strlen(char *s) {
    int n = 0;

    while (*s++ != '\0') {
        n++;
        }
    return n;
    }

/*  strcpy: copy most first n char of t to s  */
void strcpy(char *s, char *t, int n) {
    int i = 0, size_t = 0;
    /*  length of t < n  */
    if ((size_t = strlen(t)) < n) {
        printf ("n = %d is too large. there is only %d character in t\n", n, size_t);
        }
    /*  wrong:  for (i = 0; (*s = *t) != '\0' && i < n; i++) {  */
    for (i = 0; i < n && (*s = *t) != '\0'; i++) {
        s++;
        t++;
        }
    /*  size_t > n  */
    if (*s != '\0') {
        *(s+1) = '\0';
        }
    }

/*  strcat: add most first n characters of t to end of s  */
void strcat(char *s, char *t, int n) {
    int i = 0, size_t = 0;
    /*  length of t < n  */
    if ((size_t = strlen(t)) < n) {
        printf ("n = %d is too large. there is only %d character in t\n", n, size_t);
        }
    /*  advance to end of *s == '\0'  */
    while (*s != '\0') {
        s++;
        }
    /*  */
    for (i = 0; i < n && (*s = *t) != '\0'; i++) {
        s++;
        t++;
        }
    if (*s != '\0') {
        *(s+1) = '\0';
        }
    }

/*  strcmp: compare s and t, return > 0 if s > t, 0 if s == t, < 0 if s < t  */
int strcmp(char *s, char *t, int n) {
    int i = 0, size_t = 0;
    /*  length of t < n  */
    if ((size_t = strlen(t)) < n) {
        printf ("n = %d is too large. there is only %d character in t\n", n, size_t);
        }

    for (i = 0; i < n && *s == *t; i++) {
        if (*s == '\0') {
            return 0;
            }
        s++;
        t++;
        }

    if (i == n) {
        /*if (*s == '\0') {
            return 0;
            }*/
        return *s - '\0';
        }
    return *s - *t;
    }



//#include <stdio.h>

int main(void) {
    int n = 6;
    char s1[] = "i love program.";
    char s2[] = "i llve";
    char s3[] = "i love";

    if (strcmp(s2, s3, n) == 0) {
        printf ("match\n");
        }
    else {
        strcpy(s2, s3, n);
        if (strcmp(s2, s3, n) == 0) {
            printf ("correct\n");
            if (strcmp(s1, s2, n) == 0) {
                printf ("match\n");
                }
            else {
                printf ("no\n");
                *(s1+n) = '\0';
                if (strcmp(s1, s2, n) == 0) {
                    printf ("match\n");
                    }
                }
            }
        }

    for (n =3; n < 8; n++) {
        strcat(s2, s3, n);
        printf ("%s\n", s2);
        }
    }
