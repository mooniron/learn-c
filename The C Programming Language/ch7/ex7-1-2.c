/**************************************************************
* Name     :  ex7-1-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: 7.1 standard input and output
    //read from file
    prog <infile
    //output to file
    prog >infile
    //pipe
    prog | otherprog
*/


#include <stdio.h>
#include <ctype.h>

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        putchar(tolower(c));
        }   //end while

    return 0;
    }   //end function main
