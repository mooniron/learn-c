/**************************************************************
* Name     :  ex3-2-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/


#include <stdio.h>
#define MAXCOL 1000

/* escape : convert characters like '\t' '\n' to '\\t' , '\\n' when copy t to s  */
void escape(char t[], char s[]) {
    int i, j;

    j = 0;

    for (i = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            default:
                s[j++] = t[i];
                break;
            }
        }
    s[j] = '\0';
    }

/*  escapeinv : convert '\\t' '\\n' to '\t' '\n' when copy t to s  */
void escapeinv(char t[], char s[]) {
    int i, j;

    j = 0;

    for (i = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\\':
                switch (t[++i]) {
                    case 't':
                        s[j++] = '\t';
                        break;
                    case 'n':
                        s[j++] = '\n';
                        break;
                    default:
                        s[j++] = '\\';
                        s[j++] = t[i];
                        break;
                    }
                break;
            default:
                s[j++] = t[i];
                break;
            }
        }
    s[j] = '\0';
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


int main() {
    char s[MAXCOL];
    char t[MAXCOL];

    getline(t, MAXCOL);
    escape(t, s);
    printf ("%s.***", s);
    escapeinv(s,t);
    printf ("%s.***", t);
    }
