/**************************************************************
* Name     :  ex2-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月23日
**************************************************************/

/*  function :
    */

#include <stdio.h>
#include <limits.h>
#include <float.h>

/*--------------- MAIN Code Module -----------------*/
int main ()
{
    printf ("char bit size is %d.\n", CHAR_BIT);
    printf ("max char size is %d.\n", CHAR_MAX);
    printf ("MIN char size is %d.\n", CHAR_MIN);
    printf ("max int size is %d.\n", INT_MAX);
    printf ("min int size is %d.\n", INT_MIN);
    printf ("min long int size is %ld.\n", LONG_MIN);
    printf ("max long int size is %ld.\n", LONG_MAX);
    printf ("min short int size is %d.\n", SHRT_MIN);
    printf ("max short int size is %d.\n", SHRT_MAX);
    printf ("MAX unsigned char size is %d.\n", UCHAR_MAX);
    printf ("max unsigned int size is %d.\n", UINT_MAX);
    printf ("max unsigned long size is %ld.\n", ULONG_MAX);
    printf ("max unsigned short size is %d.\n", USHRT_MAX);

    return 0;
}
