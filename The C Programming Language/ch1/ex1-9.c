/**************************************************************
* Name     :  ex1-9.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : one or more banks to single blank*/

#include <stdio.h>

int main (void)
{
    int c, nextc ;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            putchar(c) ;
            /*input is a blank, find the next character which is not blank*/
            while ((nextc = getchar()) == ' ')
                ;
            /*if the char is not blank, print it*/
            putchar(nextc) ;
        }
        else
            putchar(c) ;
    }
    //printf ("\nThe number of blanks, tabs and newlines :%d, %d, %d\n", blanks, tabs, newlines) ;
    return 0 ;
}
