/**************************************************************
* Name     :  ex1-6.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : input and output character*/

#include <stdio.h>

int main(void)
{
    int c ;
    printf ("%d\n", (getchar() != EOF)) ;
    while ((c = getchar()) != EOF)
    {
        putchar(c) ;
    }
    printf ("EOF's value is %d\n", EOF);
    return 0 ;
}
