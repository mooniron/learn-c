/**************************************************************
* Name     :  ex1-16-2.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年2月15日
**************************************************************/

/* function: print the longest line of arbitrary input lines*/

#include <stdio.h>
/* the max length of a line */
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* the main function, print the longest input line */
int main(void)
{
    /* current line length */
    int len;
    /* maximum line length seen so far*/
    int max;
    /* current input line */
    char line[MAXLINE+1];
    /* longest line saved here */
    char longest[MAXLINE+1];
    max = 0;
    /*compare the current line and the longest line so far, storage the larger one and its length*/
    while ((len = getline(line, MAXLINE+1)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    /* there was a line */
    if (max > 0) {
        printf("The longest input line's length : %d\n", max);

        if (max <= MAXLINE)
            printf("The longest input line :\n%s\n", longest);
        else {
            printf("Sorry, the longest input line is too long to print.\nThe limit line length is %d.\n", MAXLINE);
            printf("The top %d character of longest input line :\n%s\n", MAXLINE, longest);
            }
        }

    return 0;
}

/* getline : resd a line into s, return length */
int getline(char s[], int slim)
{
    int c, i;

    for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        if (i < slim-1)
            s[i] = c;
        }

    if (c == '\n'){
        if (i < slim-1)
            s[i] = c;  // ingore the character after the limit length slim-2 .
        ++i;
        }

    if (i <= slim-1)
        s[i] = '\0';
    else
        // s[slim-1] is the last one of array s[slim].
        s[slim-1] = '\0';

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
