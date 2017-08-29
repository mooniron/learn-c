/**************************************************************
* Name     :  ex1-8-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : line count in input*/

#include <stdio.h>

int main (void)
{
    int nc,c ;
    while ((c=getchar()) != EOF)
    {
        if (c=='\n')
            ++nc;
    }
    printf ("\n%d\n", nc) ;
    return 0 ;
}
