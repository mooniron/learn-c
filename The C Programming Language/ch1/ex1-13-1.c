/**************************************************************
* Name     :  ex1-13-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : count digits, white spaces, others */

#include <stdio.h>

int main (void)
{
    int c, i, nwhite, nother ;
    int ndigit[10] ;
    nwhite = nother = 0;
    /* initialize the array */
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if ((c >= '0') && (c <= '9'))
            ++ndigit[c - '0'];
        else if ((c == ' ') || (c == '\t') || (c == '\n'))
            ++nwhite;
        else
            ++nother;
    }

    printf("digits are \n");
    for (i = 0; i < 10; ++i)
        printf("the count of %d is %d\n", i, ndigit[i]);
    printf("white space is %d, other is %d\n", nwhite, nother);
    return 0 ;
}
