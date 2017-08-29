/**************************************************************
* Name     :  ex5-10-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月9日
**************************************************************/

/*
example: command line arguments
    echo cmmand-line arguments

*/

#include <stdio.h>

/*  echo command-line arguments: 1st version, treat argv as an array of character pointers  */
int main(int argc, char *argv[]) {
    int i;

    for (i = 1; i < argc; i++) {
        printf("%s%s", argv[i], (i < argc-1) ? " " : "");
        }   //end for (i = 1; ...)
    printf("\n");

    return 0;
    }   //end function main
