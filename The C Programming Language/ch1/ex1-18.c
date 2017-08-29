/**************************************************************
* Name     :  ex1-16-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月15日
**************************************************************/

/* function: delete blank lines,
    and remove trailing blanks and tabs from each line of input,
    store the line to a safe place\
*/

#include <stdio.h>
/* the max length of a line */
#define MAXCOL 1000
// the max output lines
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* the main function, print the longest input line */
int main(void)
{
    int i,j,count;
    /* current line length */
    int len;
    /* new line length */
    int newlen;
    /* flag indicate the line if have only spaces and tabs */
    int flag;
    /* current input line */
    char line[MAXCOL];
    /* the output line saved here */
    char output[MAXLINE][MAXCOL];

    newlen = 0;
    j = 0;
    flag = 0;
    count = 0;

    /* get lines, delete blank lines,
    and remove trailing blanks and tabs from each line of input,
    store the line to a safe place*/
    while ((len = getline(line, MAXCOL)) > 0)
    {
        // initialize the flag to 0 for each line
        flag = 0;
        // delete the blank lines. only have one character '\n'
        if(len > 1) {

            /* assume the last character of line is '\n'.  line[len-1] = '\n'
            from the end to find the first char which is not space or tab.
            if find the not space and tab char , flag = 1. break the loop
            */
            for(i = len-2; (i >= 0) && (flag == 0); --i) {
                if((line[i] != ' ') && (line[i] != '\t')) {
                    newlen = i + 2;
                    flag = 1;
                    }
                }
            line[newlen-1] = '\n';
            line[newlen] = '\0';
            //copy the no blank lines to output
            if (flag == 1) {
                if (j < MAXLINE) {
                    copy(output[j], line);
                    }
                ++j;
                }
            }
    }

    count = j;
    /* there was a line */
    if (count > 0) {
        printf("This app remove the trailing blanks and tabs of each line, delete the blank lines.\n\n");
        printf("the total number of no blank lines is %d.\n", count);
        if (count <= MAXLINE) {
            printf("They are list below :\n");

            for (i = 0; i < count; ++i) {
                printf("%s", output[i]);
                }
            printf("\n");
            }
        else {
            printf("The limit number of lines to print is %d.\n", MAXLINE);
            printf("ah, there are too many lines to print. I are dying!!!\n");
            }
        }
/*    else {
        printf("There is no line's length > %d.\n", LEAST);
        }
*/
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
