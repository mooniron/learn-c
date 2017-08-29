/**************************************************************
* Name     :  ex7-1-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: 7.1 standard input and convertcaseput
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LOWER 01
#define UPPER 02

int (*convertcase)(int);

int main(int argc, char *argv[]) {
    int c, flag;

    //default value
    if (argc > 1) {
        flag = 0;
        }

    if (strcmp(argv[0], "lower") == 0) {
        flag = LOWER;
        }
    else if (strcmp(argv[0], "upper") == 0) {
        flag = UPPER;
        }
    else {
        flag = 0;
        }

    if (flag == 0) {
        printf("usage: lower or upper\n");
        }
    else {
       convertcase = ((flag == LOWER) ? tolower : toupper);
        while ((c = getchar()) != EOF) {
            putchar(convertcase(c));
            }   //end while
        }   //end flag == 0

    return 0;
    }   //end function main
