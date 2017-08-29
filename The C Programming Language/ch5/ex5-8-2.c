/**************************************************************
* Name     :  ex5-8-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
example: multi-dimensional array
    day_of_year: set day of year from month & day.
    month_day: set month, day from day of year.
    month_name: return name of n-th month
*/

/*  days of each month for leap and non-leap year array  */
static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, \
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/*  day of year: set day of year from month & day  */
int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
        }
    return day;
    }   //end of function day_of_year

/*  month_day: set month, day from day of year  */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
        }   //end of for(i = 1; yearday ...)
    *pmonth = i;
    *pday = yearday;
    }   //end of function month_day


/*  month_name: return name of n-th month  */
char *month_name(int n) {

    /*  warning: ISO C++ forbids converting a string constant to 'char*' [-Wpedantic]  */
    /*  char *name[]: an array of pointers; char (*name)[]: a pointer to array  */
    static char *name[] = { \
        "Illegal month", "January", "February", "March", "April", "May", "June", \
        "July", "August", "September", "October", "November", "December" \
        };   //end char *name[] initialize

    return (n < 1 || n> 12) ? name[0] : name[n];
    }   //end function char *month_name


#include <stdio.h>

/*  main function  */
int main(void) {
    int i, month, day, year, yearday;
    int *pmonth = &month, *pday = &day;

    month = 3;
    day = 3;
    year = 2017;
    yearday = 321;

    for (i = 1; i < 10; i++) {
        yearday = day_of_year(year, month, day);
        printf("yearday is %d, year is %d, month is %d, day is %d\n", yearday, year, month, day);
        month_day(year, yearday, pmonth, pday);
        printf ("*pmonth = %d, *pday = %d\n", *pmonth, *pday);
        printf ("month %d name is %s\n", month, month_name(month));
        month++;
        day++;
        year--;
        }   //end of for(i = 10; ...)

    }   //end of function main
