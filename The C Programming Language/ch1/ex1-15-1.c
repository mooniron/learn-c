/**************************************************************
* Name     :  ex1-15.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/* function : temperature conversion, from fahrenheit to celsius
    and from celsius to fahrenheit
*/

#include <stdio.h>

// prototype function
float fahr_cel(int fahr);
float cel_fahr(int cel);

int main(void)
{
    int i ;
    i = 0 ;

    printf("Fahrenheit-Celsius Table\n");
    for (i = 0; i < 200; i = i + 20)
    {
        printf("fahr = %3d, cel = %6.1f\n", i, fahr_cel(i));
    }

    printf("Celsius-Fahrenheit Table\n");
    for (i = -20; i < 100; i = i + 10)
    {
        printf("cel = %3d, fahr = %6.1f\n", i, cel_fahr(i));
        }
}

// fahrenheit to celsius function
float fahr_cel(int fahr)
{
    float cel;
    cel = 5.0/9.0 * (fahr - 32.0);

    return cel;
}

// celsius to fahrenheit function
float cel_fahr(int cel)
{
    float fahr;
    fahr = 9.0/5.0 * cel + 32.0;

    return fahr;
}
