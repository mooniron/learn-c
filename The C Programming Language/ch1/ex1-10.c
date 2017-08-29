/**************************************************************
* Name     :  ex1-10.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : replace tab by \t, replace backspace by \b, replace backslash by \\*/

#include <stdio.h>

int main (void)
{
    int c ;
    while ((c = getchar()) != EOF)
    {
        /*replace tab to \t*/
        if (c == '\t')
        {
            putchar('\\') ;
            putchar('t') ;
        }
        /*replace backspace to \b, but can not verify the result*/
        else if (c == '\b')
        {
            putchar('\\') ;
            putchar('b') ;
        }
        /*replace backslash to \\*/
        else if (c == '\\')
        {
            putchar('\\') ;
            putchar('\\') ;
        }
        else
            putchar(c) ;
    }
    return 0 ;
}
