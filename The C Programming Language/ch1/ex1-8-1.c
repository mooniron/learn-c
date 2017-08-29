/**************************************************************
* Name     :  ex1-8-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : input character count*/

#include <stdio.h>

int main (void)
{
    long nc ;
    nc = 0 ;
    while (getchar() != EOF)
        ++nc ;
    printf ("%ld\n", nc) ;
    return 0 ;
}
