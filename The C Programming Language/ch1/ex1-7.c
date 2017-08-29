/**************************************************************
* Name     :  ex1-7.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : input and output character*/

#include <stdio.h>

int main(void)
{
    int c ;
    bool d ;
    printf ("%d\n", (getchar() != EOF)) ;
    while ((c = getchar()) != EOF)
    {
        if (c != '\n')
            {
                d = c != EOF ;
                printf ("%d\n", d) ;
            }
    }
    printf ("EOF is %d\n", EOF) ;
    return 0 ;
}
