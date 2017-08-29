/**************************************************************
* Name     :  ex1-11.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : count characters, words, lines*/

#include <stdio.h>
/*inside a word*/
#define IN 1
/*outside a word*/
#define OUT 0

int main (void)
{
    int c, nc, nw, nl, state;
    nc = nw = nl = 0;
    state = OUT;
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if ((c == ' ') || (c == '\t') || (c == '\n'))
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }
    printf ("\nThe total input characters, words, lines are %d, %d, %d\n", nc, nw, nl);
    return 0 ;
}
