/**************************************************************
* Name     :  ex7-4-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: formatted standard output scanf
    //arg1 and arg2 ... are pointers responding to format argument;
    int scanf(char *format, arg1, arg2, ...);
    //read string instead of standard input
    int sscanf(char *string, char *format, ...);

1.  rudimentary calculator of chapter 4:
    written with scanf to do the input conversion;
warning:
    all arguments of scanf and sscanf are pointers.

rudimentary calculator:
read dates of form:
    12 Dec 2017
    mm/dd/yy;
*/


#include <stdio.h>

int getline(char *, int);
/*  rudimentary calculator && dates  */
int main(void) {
    double sum, v;
    //dates
    int day, month, year;
    char monthname[20], line[1000];


    //calculator
    sum = 0;
    while (scanf("%1lf", &v) == 1) {
        printf("\t%.2lf\n", sum += v);
        }

    //dates
    while (getline(line, sizeof(line)) > 0) {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3) {
            // 25 Dec 2017 form
            printf("valid: %s\n", line);
            }
        else if (sscanf(line, "%d/%d/%d", &month, &day, &year)) {
            // mm/dd/yy form
            printf("valid: %s\n", line);
            }
        else {
            // invalid form
            printf("invalid: %s\n", line);
            }   //end if
        }   //end while dates

    return 0;
    }   //end function main


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
