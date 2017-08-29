/**************************************************************
* Name     :  ex1-17.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月16日
**************************************************************/

/* function: print the lines of input : length > 80 */

#include <stdio.h>
/* the max length of a line */
#define MAXLINE 1000
/* the max number of lines to print */
#define MAXPRINT 1000
/* the low limit length of the line to print */
#define LEAST 80

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* the main function, print the longest input line */
int main(void)
{
    /* current line length */
    int len;
    /* the number of print lines */
    int i;
    /* the total number of print lines */
    int count;
    /* the lines :length > LEAST */
    char leastline[MAXPRINT][MAXLINE];
    /* current input line */
    char line[MAXLINE];
    /* longest line saved here */
    //char longest[MAXLINE];

    i = 0;
    count = 0;

    /*compare the current line and the longest line so far, storage the larger one and its length*/
    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > LEAST)
        {
            if (i < MAXPRINT) {
                copy(leastline[i], line);
                }
            //
            ++i;
        }
    }

    count = i;

    /* there was a line */
    if (count > 0) {
        printf("the total number of the length > %d lines is %d.\n", LEAST, count);
        if (count <= MAXPRINT) {
            printf("They are list below :\n");

            for (i = 0; i < count; ++i) {
                printf("%s", leastline[i]);
                }
            printf("\n");
            }
        else {
            printf("The limit number of lines to print is %d.\n", MAXPRINT);
            printf("ah, there are too many lines to print. I are dying!!!\n");
            }
        }
    else {
        printf("There no line's length > %d.\n", LEAST);
        }

    return 0;
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
