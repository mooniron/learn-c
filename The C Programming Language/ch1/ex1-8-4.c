/**************************************************************
* Name     :  ex1-8-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : line count in input*/

#include <stdio.h>

int main (void)
{
    int c, blanks, tabs, newlines ;
    blanks = 0 ;
    tabs = 0 ;
    newlines = 0 ;
    while ((c=getchar()) != EOF)
    {
        if (c == ' ')
            ++blanks ;
        if (c == '\t')
            ++tabs ;
        if (c == '\n')
            ++newlines ;
    }
    printf ("\nThe number of blanks, tabs and newlines :%d, %d, %d\n", blanks, tabs, newlines) ;
    return 0 ;
}
