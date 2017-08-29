/**************************************************************
* Name     :  ex4-14-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月5日
**************************************************************/

/*
excerse 4-14:
    write a macro swap(t, x, y) that interchanges two arguments of type t.
*/

#include <stdio.h>
/*  interchange x and y  */
#define swap(t, x, y) \
    do { \
        /*  define "safe ## x ## y" variable  */ \
        t safe ## x ## y; \
        safe ## x ## y = x; \
        x = y; \
        y = safe ## x ## y; \
    } while(0)


int main() {
    int ix, iy;

    ix = 32;
    iy = 56;

    printf ("before swap, x = %d, y = %d\n", ix, iy);
    swap(int, ix, iy);
    printf ("after swap, x = %d, y = %d\n", ix, iy);
    }
