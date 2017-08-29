/**************************************************************
* Name     :  ex5-1-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  e2017年3月5日
**************************************************************/

/*
example:
    swap: pointer version
*/
#include <stdio.h>

/*  swap: interchange *px and *py  */
//  int *px : pointer declaration px argument.
void swap(int *px, int *py) {
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
    }

int main(void) {
    int x = 1, y = 2, z[10];
    int *ip;
    /*  ip now points to x  */
    ip = &x;
    /*  y is now 1  */
    y = *ip;
    /*  x is now 0  */
    *ip = 0;
    /*  ip now points to z[0], ip == z  */
    ip = & z[0];
    *ip = y;
    *ip += 1;
    ++*ip;
    z[1] = 8;
    /*  z[0] add 1, ip point z[1]  */
    ++*(ip++);
    /*  z[1] add 1  */
    (*ip)++;
    printf ("*ip = %d, z[0] = %d, z[1] = %d\n", *ip, z[0], z[1]);
    void *vp = (void *)ip;
    printf ("vp = %p\n", vp);

    int *ip1 = &y;
    //printf ("*ip1 = %d\n", *ip1);
    /*  error: type *inp1 is int, type &y is int*  */
    //*ip1 = &y;
    printf ("*ip1 = %d\n", *ip1);

    /*  swap  */
    /*  pointer must be initialized befor assigned, e.g. *px =3  */
    int *px = &x, *py = &y;
    x = 3;
    y = 2;
    *px = 3;
    *py = 2;

    swap(&x, &y);
    printf ("x = %d; y = %d\n", x, y);
    swap(px, py);
    printf ("*px = %d, *py = %d\n", *px, *py);
    }
