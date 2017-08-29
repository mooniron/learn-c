/**************************************************************
* Name     :  ex2-8.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月24日
**************************************************************/

#include <stdio.h>

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

/* bitcountfast : count 1 bits in x faster  */
int bitcountfast(unsigned x) {
    int b;
    // if x = 0, b = 0
    for (b = 0; x != 0; b++) {
        x &= x - 1;
        }
    return b;
    }

int main() {
    unsigned int x;
    int i;

    x = 0x23;

    for (i = 0; i < 5; i++) {
        if (bitcount(x) == bitcountfast(x)) {
            printf ("there are %d 1-bits in 0x%x \n", bitcount(x), x);
            }
        else {
            printf ("ERROR\n");
            }
        x += 1;
        }
    }

