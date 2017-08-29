/**************************************************************
* Name     :  ex2-8.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月24日
**************************************************************/

#include <stdio.h>
#define MAXCOL 1000

/*  rightrot(x, n): return the value of the integer x rotated to the right by n positions
    */
unsigned rightrot(unsigned x, int n) {
    //  find the highest 1 position
    int len;
    unsigned tmp;
    tmp = x;
    for (len = 0; tmp != 0; len++) {
        tmp = tmp >> 1;
        }
    if (len <= n + 1 ) {
        return x;
        }
    else {
        return (x >> (n + 1)) | ((x & ~(~0 << (n + 1))) << (len - n - 1));
        }
    }

/*  bitcount : count 1 bits in x  */
int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x >>= 1) {
        if (x & 01) {
            b++;
            }
        }
    return b;
    }

int main() {
    unsigned int x;
    int i;

    x = 0x23;

    for (i = 0; i < 5; i++) {
        printf ("rightrot(0x%x, 2) is 0x%x\n", x, rightrot(x, 2));
        x = x >> 1;
        }
    }

