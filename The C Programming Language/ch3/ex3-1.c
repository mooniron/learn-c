/**************************************************************
* Name     :  ex3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月25日
**************************************************************/


#include <stdio.h>
#define MAX 10

/*  binsearch: find x in v[0] <= v[1] <= v[2] << .. << v[n-1]
    */

int binsearch(int x, long int v[], long int n) {
    long int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            //high = mid + 1;
            high = mid - 1;
            }
        else if(x > v[mid]) {
            low = mid + 1;
            }
        else {
            /*  found match  */
            return mid;
            }
        }
    /*  no match  */
    return -1;
    }

/*  binsearch: one test in loop version  */
int binsearch2(int x, long int v[], long int n) {
    long int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if  (x < v[mid]) {
            high = mid - 1;
            }
        if (x > v[mid]) {
            low = mid + 1;
            }
        if (x == v[mid]) {
            return mid;
            }
        }
    return -1;
    }

int main() {
    long int i;
    long int v[MAX];
    int p = 0;
    int x = 1;

    for (i = 0; i < MAX; i++) {
        v[i] = i;
        }
    //p = binsearch(x, v, MAX);
    //printf ("the position is %d\n", p);
    for (i = 0; p != -1; i++) {
        if ((p = binsearch2(x, v, MAX)) > -1) {
            printf ("the position is %d\n", p);
            }
        else {
            printf ("NO MATCH, x is %d\n", x);
            }
        x += 2;
        }

    }
