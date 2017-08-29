/**************************************************************
* Name     :  ex1-14.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*function : print the histogram of the frequency of input words.
  from a to z ann 0 to 9
*/

#include <stdio.h>
/*extra height of the histogram*/
#define HEIGHT 1


int main (void)
{
    int c, maxfreq, i, j ;
    int hist[37] ;
    maxfreq = 0 ;
    /* initialize the histogram array */
    for (i = 0; i< 37; ++i)
        hist[i] = 0;

    /* get input words and storge the length of words to an array*/
    while ((c = getchar()) != EOF)
    {
        /* count a to z, hist[0 to 25] */
        if ((c >= 'a') && (c <= 'z'))
            ++hist[c - 'a'] ;
        /* count A to Z, hist[0 to 25] */
        else if ((c >= 'A') && (c <= 'Z'))
            ++hist[c - 'A'] ;
        /* count 0 to 9, hist[26 to 35] */
        else if ((c >= '0') && (c <= '9'))
            ++hist[c - '0' + 26] ;
        /* count other characters, hist[37] */
        else
            ++hist[36] ;
    }
    /* get the max frequency of the character*/
    for (i = 0; i < 37; ++i)
    {
        if (hist[i] > maxfreq)
            maxfreq = hist[i] ;
    }
    /* print the histogram according to the data of the array*/
    printf ("\nThe histogram of the length of input word\n");
    for (i = maxfreq + HEIGHT; i > 0; --i)
    {
        for (j = 0; j < 37; ++j)
        {
            /* if the frequency of character greater than line number,
            then print '* ', else print white space */
            if (hist[j] >= i)
                printf("* ");
            else
                printf("  ");
        }
        putchar('\n') ;
    }
    /* print the letter of a to z */
    for (i = 0; i < 26; ++i)
        printf("%c ", 'a'+i) ;
    /* print the digit of 0 to 9 */
    for (j = 0; j < 10; ++j)
        printf("%d ", j) ;
    printf("other\n") ;
    for (i = 0; i< 37; ++i)
        printf("%d ", hist[i]);
    printf("\n");
    return 0 ;
}
