/**************************************************************
* Name     :  ex2-6.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月24日
**************************************************************/

/*  setbits: get n bits from position p in s[]
    */

#include <stdio.h>
#define MAXCOL 1000

/*  setbits: get n bits from position p in s[]
    */
unsigned setbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~ (~0 << n);
    }

/*  setbits: return x with the n bits that begin at position p set to the rightmost n bits of y,
    leaving the other bits unchanged  */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    /*  ((~0 << (p + 1)) | ~(~0 << (p + 1 - n))) : 1111{p - n 0}111
        ((y & ~(~0 << n)) << (p + 1 -n)) : 00000{n bit 1}0000*/
    return (x & ((~0 << (p + 1)) | ~(~0 << (p + 1 - n)))) | ((y & ~(~0 << n)) << (p + 1 -n));
    }

/*  invert(x, p, n): return x with the n bits that begin at position p inverted,
    leaving the others unchanged  */
unsigned invert(unsigned x, int p, int n) {
    return x ^ ((~(~0 << n)) << (p + 1 - n));
    }

int main() {
    unsigned int x;
    unsigned int y;
    int i;

    x = 0x23;
    y = 0x12;

    // setbits x
    printf ("setbits(0x%x, 4, 3) is 0x%x\n", x, setbits(x, 4, 3));
    // invert
    printf ("invert(0x%x, 4, 3) is 0x%x\n", x, invert(x, 4, 3));
    for (i = 0; i < 3; i++) {
        printf ("setbits(0x%x, 4, 3, 0x%x) is 0x%x\n", x, y, setbits(x, 4, 3, y));
        x += 3;
        y += 2;
        }
    }
