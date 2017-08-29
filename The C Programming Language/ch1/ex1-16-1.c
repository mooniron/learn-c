/**************************************************************
* Name     :  ex1-16-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月15日
**************************************************************/

/* function: print the longest line of input */

#include <stdio.h>
/* the max length of a line */
#define MAXLINE 1000

/*  pass the location or address of the beginning item in the array.
    call the function can modify the value of the array.
*/
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
    char line[MAXLINE];
    /* longest line saved here */
    char longest[MAXLINE];
    max = 0;
    /*compare the current line and the longest line so far, storage the larger one and its length*/
    while ((len = getline(line, MAXLINE)) > 0)
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
        printf("The longest input line :\n%s\n", longest);
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
