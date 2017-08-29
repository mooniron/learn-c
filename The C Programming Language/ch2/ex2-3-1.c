/**************************************************************
* Name     :  ex2-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月23日
**************************************************************/

/*  function : convert a string of digit s to its numeric value
    */
#include <stdio.h>

/*  atoi: convert s to integer  */
int atoi(char s[]) {
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
        n = 10 * n + (s[i] - '0');

        }
    return n;
    }

/*  lower: convert c to lower case  */
int lower(int c) {

    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
        }
    else {
        return c;
        }
    }

/*  rand: return pseudo-random integer on 0..32767  */
int rand(void) {
    next = next * 1103515245 + 12345;
    return (unigned int) (next / 65536) % 32768;
    }

/*  srand: set seed for rand()  */
void srand(unsigned int seed) {
    next = seed;
    }
