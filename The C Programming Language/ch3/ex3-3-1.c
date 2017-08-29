/**************************************************************
* Name     :  ex3-3-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#define MAXCOL 1000

/*  expand(s1[], s2[]) : expand shorthand notations like a-z in the s1 into abc...xyz in s2.
    Allow for letters of either case and digits, and be prepared to handle a-b-c and a-z0-9 and -a-z.  */
void expand(char s1[], char s2[]) {
    int i, j, k;

    i = j = k = 0;

    while (s1[i] != '\0') {
        //  expand a-z
        if (s1[i] >= 'a' && s1[i] <= 'z') {
            s2[j++] = s1[i++];
            //  a-z-a
            while (s1[i] == '-' && (s1[i+1] >= 'a' && s1[i+1] <= 'z')) {
                //  a-z
                if (s1[i+1] >= s1[i-1]) {
                    for (k = 0; k < s1[i+1] - s1[i-1]; k++) {
                        s2[j] = s2[j-1] + 1;
                        j++;
                        }
                    i += 2;
                    }
                //  z-a
                else {
                    for (k = 0; k < s1[i-1] - s1[i+1]; k++) {
                        s2[j] = s2[j-1] - 1;
                        j++;
                        }
                    i += 2;
                    }
                }
            }
        //  expand capital A-Z
        else if (s1[i] >= 'A' && s1[i] <= 'Z') {
            s2[j++] = s1[i++];
            //  A-Z-A
            while (s1[i] == '-' && (s1[i+1] >= 'A' && s1[i+1] <= 'Z')) {
                //  A-Z
                if (s1[i+1] >= s1[i-1]) {
                    for (k = 0; k < s1[i+1] - s1[i-1]; k++) {
                        s2[j] = s2[j-1] + 1;
                        j++;
                        }
                    i += 2;
                    }
                //  Z-A
                else {
                    for (k = 0; k < s1[i-1] - s1[i+1]; k++) {
                        s2[j] = s2[j-1] - 1;
                        j++;
                        }
                    i += 2;
                    }
                }
            }
        // expand digits 0-9
        else if (s1[i] >= '0' && s1[i] <= '9') {
            s2[j++] = s1[i++];
            //  0-9-0
            while (s1[i] == '-' && (s1[i+1] >= '0' && s1[i+1] <= '9')) {
                //  0-9
                if (s1[i+1] >= s1[i-1]) {
                    for (k = 0; k < s1[i+1] - s1[i-1]; k++) {
                        s2[j] = s2[j-1] + 1;
                        j++;
                        }
                    i += 2;
                    }
                //  9-0
                else {
                    for (k = 0; k < s1[i-1] - s1[i+1]; k++) {
                        s2[j] = s2[j-1] - 1;
                        j++;
                        }
                    i += 2;
                    }
                }
            }
        //  others
        else {
            s2[j++] = s1[i++];
            }
        }
    // end flag '\0'
    s2[j] = '\0';
    }

/* getline : resd a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    {
        s[i] = c;
        }
    if (c == '\n') {
        s[i] = c;
        ++i;
        }

    s[i] = '\0';
    return i;
}

/*  main: test expand(s1, s2)  */
int main() {
    int i = 0;
    char s1[MAXCOL];
    char s2[MAXCOL];

    for (i = 0; i < 3; i++) {
        getline(s1, MAXCOL);
        expand(s1, s2);
        printf ("%s", s2);
        }
    }
