/**************************************************************
* Name     :  ex4-12-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月3日
**************************************************************/

/*
example:
    printd: itoa recursive solution.
    qsort: quick sort recursion version，
    algorithms: by C.A.R Hoare in 1962
        given an array, one element is chosen and the others partitioned in two subsets
        - those less than the partiton element and those greater than or equal to it.
        the same process is then applied recursively to the two subsets. when a subset has
        fewer than two elements, it doesn't need any sorting, this stops the recursion.
*/

#include <stdio.h>

/*  qsort: sort v[left]...v[right] into increasing order  */
void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);

    /*  do nothing if array contains fewer than two elements  */
    if (left >= right) {
        return;
        }
    /*  swap middle and left element, move partition element  */
    swap(v, left, (left + right) / 2);
    /*  to v[0]  */
    last = left;
    /*  partition  */
    for (i = left + 1; i <= right; i++) {
        /*  move less than v[left] element to left of last  */
        if (v[i] < v[left]) {
            swap(v, ++last, i);
            }
        }
    /*  swap left (middle) to the last  */
    swap(v, left, last);
    /*  recursive less partition  */
    qsort(v, left, last-1);
    /*  recursive greater*/
    qsort(v, last+1, right);
    }

/*  swap: interchange v[i] and v[j]  */
void swap(int v[], int i, int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    }

/*  printd: print n in decimal  */
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
        }
    if (n / 10) {
        printd(n / 10);
        }
    putchar(n % 10 + '0');
    }

int main() {
    int i;
    printd(-1234);
    int s[] = {1, 2, 8, 99, 34, 27, 87, 132, 72};
    qsort(s, 0, 9);
    for (i = 0; i < 10; i++) {
        printf ("%d, ", s[i]);
        }

    }
