/**************************************************************
* Name     :  ex1-8-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : input character count*/

#include <stdio.h>

int main (void)
{
    float nc ;

    for (nc = 0.0; getchar() != EOF; ++nc)
        ;
    printf ("%.0f\n", nc) ;
    return 0 ;
}
