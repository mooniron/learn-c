/**************************************************************
* Name     :  ex1-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月13日
**************************************************************/

#include <stdio.h>
/*print Celsius-Fahrenheit table for celsius = -20, -10, ...,100 */
/*--------------- MAIN Code Module -----------------*/
main ()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = -20;
    /* lower limit of temperature scale */
    upper = 100.0;
    /* upper limit */
    step = 10.0;
    /* step size */

    celsius = lower;
    printf("Celsius-Fahrenheit Table\n");
    printf("\tfrom -20 to 100\n");
    while (celsius <= upper)
    {
        fahr = 9.0 / 5.0 * celsius + 32.0;
        printf("%3.0f%9.2f\n", celsius, fahr);
        celsius = celsius + step;
    }

}
