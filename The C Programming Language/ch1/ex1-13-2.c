/**************************************************************
* Name     :  ex1-13-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : print the histogram of the length of input words */

#include <stdio.h>
/*inside a word*/
#define IN 1
/*outside a word*/
#define OUT 0
/*max height of the histogram*/
//#define HEIGHT 20
/*max number of input word*/
#define NUMWORD 1000

int main (void)
{
    int c, state, len, maxlen, numword, i, j ;
    int hist[NUMWORD] ;
    state = OUT ;
    numword = 0 ;
    len = 0 ;
    maxlen = 0;
    /* get input words and storge the length of words to an array*/
    while ((c = getchar()) != EOF)
    {
        /* if word, count the length of the word */
        if ((c != ' ') && (c != '\t') && (c != '\n'))
        {
            state = IN;
            ++len;
        }
        else if (state == IN)
        {
            state = OUT ;
            /* get the end of the word, storge the length in array. */
            hist[numword] = len ;
            /* initialize to find next word */
            len = 0 ;
            ++numword ;

        }
    }

    /* get the max length of input words */
    for (i = 0; i < numword; ++i)
    {
        if (hist[i] > maxlen)
            maxlen = hist[i];
    }
    /* print the histogram according to the data of the array*/
    printf ("\nThe histogram of the length of input word\n");
    for (i = maxlen+1; i > 0; --i)
    {
        for (j = 0; j < numword; ++j)
        {
            /* if the length of word greater print line number,
            then print '*', else print white space */
            if (hist[j] >= i)
                printf(" * ");
            else
                printf("   ");
        }
        putchar('\n') ;
    }
    /* print the length of each word */
    for (j = 0; j < numword; ++j)
        printf(" %d ", hist[j]) ;
    printf("\n") ;
    return 0 ;
}
