/**************************************************************
* Name     :  ex1-16-2.c
* Author   :  Bronze Lee
* Version  :  0.3
* Date     :  2017年2月15日
**************************************************************/

/*  function: print the longest line of arbitrary input lines
    the special version : external variable and function
    */

#include <stdio.h>
/* the max length of a line */
#define MAXLINE 1000

/*  maximum length seen so far  */
int max;
/*  current input line  */
char line[MAXLINE];
/*  longest line saved here  */
char longest[MAXLINE];
/*  function declaration  */
int getline();
void copy();

/* the main function, print the longest input line */
int main(void)
{
    /* current line length */
    int len;
    /* maximum line length seen so far*/
    extern int max;
    extern char longest[];
    /* current input line */
    //char line[MAXLINE+1];
    /* longest line saved here */
    //char longest[MAXLINE+1];
    max = 0;
    /*compare the current line and the longest line so far, storage the larger one and its length*/
    while ((len = getline()) > 0)
    {
        if (len > max)
        {
            max = len;
            copy();
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
int getline(void)
{
    int c, i ;
    extern char line[];

    for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        if (i < MAXLINE)
            line[i] = c;
        }

    if (c == '\n'){
        if (i < MAXLINE)
            line[i] = c;  // ingore the character after the limit length slim-2 .
        ++i;
        }

    if (i <= MAXLINE)
        line[i] = '\0';
    else
        // s[slim-1] is the last one of array s[slim].
        line[MAXLINE] = '\0';

    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(void)
{
    int i;
    extern char line[],longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
