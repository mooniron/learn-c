/**************************************************************
* Name     :  ex5-9-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercise 5-9:
    rewrite day_of_year and month_day with pointers instead of indexing
*/


/*
exercise 5-8:
    add error warning for day_of_year, month_day
*/

/*
example: multi-dimensional array
    day_of_year: set day of year from month & day.
    month_day: set month, day from day of year.
*/


/*  days of each month for leap and non-leap year array  */
static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/*  day of year: set day of year from month & day  */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

    /*  if month and day are valid  */
    if (month >= 1 && month <= 12 && day > 0 && day <= daytab[leap][month]) {
        for (i = 1; i < month; i++) {
            /*  daytab[leap][i] == *(*(daytab + leap) + i)  */
            day += *(*(daytab + leap) + i);
            }
        return day;
        }
    /*  month or day is invalid, return -1  */
    else {
        //printf ("month %d or day %d is not valid\n", month, day);
        return -1;
        }  //end if (month >= 1 ...)

    }   //end of function day_of_year

/*  month_day: set month, day from day of year  */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap, days;
    char *p;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    /*  total days one year  */
    days = leap ? 366 : 365;

    //p = &daytab[leap][1];
    p = daytab[leap];

    if (yearday > 0 && yearday <= days) {
        for (i = 1; yearday > daytab[leap][i]; i++) {
            //yearday -= daytab[leap][i];
            yearday -= *++p;
            }   //end of for(i = 1; yearday ...)
        *pmonth = i;
        *pday = yearday;
        }   //end if (yearday > 0 ...)
    /*  yearday is not valid  */
    else {
        //printf ("yearday %d is not valid for year %d\n", yearday, year);
        *pmonth = -1;
        *pday = -1;
        }
    }   //end of function month_day


#include <stdio.h>

/*  main function  */
int main(void) {
    int i, month, day, year, yearday;
    int *pmonth = &month, *pday = &day;

    month = -1;
    day = 3;
    year = 2017;
    yearday = 321;

    for (i = 1; i < 10; i++) {
        yearday = day_of_year(year, month, day);
        if (yearday > 0) {
            printf("yearday is %d, year is %d, month is %d, day is %d\n", yearday, year, month, day);
            //printf("*daytab[0] = %d\n", *daytab[0]);
            }
        else {
            printf("error: month %d or day %d is not valid for year %d\n", month, day, year);
            }
        year--;
        //yearday = 366;
        month_day(year, yearday, pmonth, pday);
        if (*pmonth > 0) {
            printf("year = %d, *pmonth = %d, *pday = %d\n", year, *pmonth, *pday);
            }
        else {
            printf("yearday %d is not valid for year %d\n", yearday, year);
            }
        month += 2;
        day += 9;
        }   //end of for(i = 10; ...)

    return 0;
    }   //end of function main
