/**************************************************************
* Name     :  ex1-15.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/* function : define a function of power m, b
   power(2,5)=32
*/

#include <stdio.h>

int power(int m, int n);

/* test power function */
int main(void)
{
    int i;
    for (i = 0; i < 10; ++i)
        printf("i=%d, power(2,i) = %d, power(-3,i) = %d\n", i, power(2, i), power(-3, i));

    return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int i, p;
    p=1;

    for (i = 1; i <= n; ++i)
        p = p * base;

    return p;
}
