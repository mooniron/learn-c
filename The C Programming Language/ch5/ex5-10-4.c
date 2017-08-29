/**************************************************************
* Name     :  ex5-10-4.c
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
//char *strstr(char *s, char *t);

/*  find: print lines that match pattern from 1st arg   */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    /*  (*++argv)[0] == **++argv  */
    while (--argc > 0 && (*++argv)[0] == '-' ) {
        //while (c = *++(*argv))
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
                }   //end switch(c)
            }   //end while(c = *++argv[0])
        }   //end while (--argc > 0)

    if (argc != 1) {
        printf ("Usage: find -x -n pattern\n");
        }
    else {
        while (getline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineno);
                    }
                printf("%s", line);
                found++;
                }   //end if ((strstr...)
            }   //end while (getline...)
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
