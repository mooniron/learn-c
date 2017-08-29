/**************************************************************
* Name     :  ex1-5.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月14日
**************************************************************/

/*print fahrrenheit to celsius from 0 to 300 */

#include <stdio.h>
/*symbolic constants*/
#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void)
{
    int fahr;
    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
    {
        printf("%3d%9.1f\n", fahr, (5.0/9.0) * (fahr-32));
        }

}
