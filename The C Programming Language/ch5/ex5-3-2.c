/**************************************************************
* Name     :  ex5-3-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  e2017年3月6日
**************************************************************/

/*
example: pointer and array
    strlen: return length of strings
*/

#include <stdio.h>

/*  size of arr store integers  */
#define SIZE  100

int strlen(char *);

int main(void) {
    int i, len;
    char arr[SIZE];
    char *ptr;

    ptr = arr;
    /*  string constant  */
    len = strlen("hello, world");
    //strlen(arr);
    //strlen(ptr);
    printf ("%d\n", len);
    }

/*  strlen: return length of strings  */
int strlen(char *s) {
    int n;

    for (n = 0; *s != '\0'; s++) {
        n++;
        }
    return n;
    }
