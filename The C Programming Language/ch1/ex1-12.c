/**************************************************************
* Name     :  ex1-12.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : count characters, words, lines. And print one word per line*/

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
        if ((c != ' ') && (c != '\t') && (c != '\n'))
        {
            state = IN;
            putchar(c);
        }
        else if (state == IN)
        {
            state = OUT;
            ++nw;
            putchar('\n');
        }
    }
    printf ("\nThe total input characters, words, lines are %d, %d, %d\n", nc, nw, nl);
    return 0 ;
}
