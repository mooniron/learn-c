/**************************************************************
* Name     :  ex1-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月13日
**************************************************************/

#include <stdio.h>
/*print Fahren-Celsius table for fahr = 0, 20, ...,300 */
/*--------------- MAIN Code Module -----------------*/
main ()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    /* lower limit of temperature scale */
    upper = 300.0;
    /* upper limit */
    step = 20.0;
    /* step size */

    fahr = lower;
    printf("Fahrenheit-Celsius Table\n");
    printf("\tfrom 0 to 300\n");
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f%9.2f\n", fahr, celsius);
        fahr = fahr + step;
    }

}
