/**************************************************************
* Name     :  ex1-19.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月15日
**************************************************************/

/* function: reverse the input each line at a time */

#include <stdio.h>
/* the max col of output*/
#define MAXCOL 1000
/* the max line of output */
#define MAXLINE 1000

/*  pass the location or address of the beginning item in the array.
    call the function can modify the value of the array.
*/
int getline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char outstr[], char instr[]);

/* the main function, print the longest input line */
int main(void)
{
    /* current line length */
    int len;
    /* current line number of output */
    int i;
    /* total output line number */
    int count;
    /* current input line */
    char line[MAXCOL];
    /* store lines in output  */
    char output[MAXLINE][MAXCOL];

    i = 0;
    count = 0;
    /*  reverse the input line, store the line in output[i]  */
    while ((len = getline(line, MAXCOL)) > 0)
    {
        if (i < MAXLINE) {
            reverse(output[i], line);
            }
        ++i;
    }

    count = i;
    /* there was a line */
    if (count > 0) {
        printf("\n\nreverse the input each line at a time\n\n");
        printf("the total number of lines is %d.\n", count);
        if (count <= MAXLINE) {
            printf("They are list below :\n\n");

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
    else {
        printf("ERROR: NO INPUT\n");
        }

    return 0;
}

/* getline : read a line into s, return length */
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

/* reverse : reverse input char array */
void reverse(char output[], char input[])
{
    int i, len;
    //  the real length of revese characters
    int revlen;
    char c;
    i = len = revlen = 0;
    //  get the length of input char array
    while((c = input[i]) != '\0') {
        ++i;
        }

    /*  if a line, reverse the characters before the '\n'
        else reverse the characters before the '\0'.
        store the length of reverse characters  */
    len = i;
    //  '\0' : the end of a string
    output[len] = '\0';
    //  if a line
    if (input[len - 1] == '\n') {
        revlen = len - 2;
        output[len - 1] = input[len - 1];
        }
    //  not a line
    else {
        revlen = len - 1;
        }
    //  reverse the revlen length of characters
    for (i = 0; i <= revlen; ++i) {
        output[revlen - i] = input[i];
        }

}
