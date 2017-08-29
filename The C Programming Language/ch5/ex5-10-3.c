/**************************************************************
* Name     :  ex5-10-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月9日
**************************************************************/

/*
example: command line arguments
    grep pattern: find and print lines that match pattern from 1st arg
*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char *line, int max);
char *strstr(char *s, char *t);

/*  find: print lines that match pattern from 1st arg   */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int found = 0;

    if (argc != 2) {
        printf("Usage: find pattern\n");
        }
    else {
        while (getline(line, MAXLINE) > 0) {
            /*  call local strstr, not the one in <string.h>  */
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
                }   //end if
            }   //end while
        }   //end else

    return found;
    }   //end function main

int getline(char *line, int lim) {
    int c, len;

    len = 0;
    while (len < lim - 1 && (c = getchar()) != EOF && c != '\n') {
        *line++ = c;
        len++;
        }   //end while (len < lim - 1 ...)

    if (c == '\n') {
        *line++ = c;
        len++;
        }   //end if (c == '\n')
    *line = '\0';

    return len;
    }

/*  strstr: return a pointer to the first occurrence of the string t in the string s,
    or NULL if there is non.
*/
char *strstr(char *s, char *t) {

    char *temps, *tempt;

    while (*s != '\0') {
        for (temps = s, tempt = t; *temps++ == *tempt++;) {
            if (*tempt == '\0') {
                return s;
                }
            }   //end for (temps = s...)
        s++;
        }   //end while (*s != '\0')

    return NULL;
    }
