/**************************************************************
* Name     :  ex4-12-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月3日
**************************************************************/

/*
exercise 4-12:
    adapt the ideas of printd to write a recursive version of itoa;
    that is, convert an integer into a sting by calling a recursive routine.
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

/*  itoa: recursive version  */
int itoa(int n, char s[], int index) {
    int i = index;
    /*  only excute at first time except the largest negative integer  */
    /*  for largest negative integer pow(2, width-1) is itself after n=-n  */
    if (n < 0) {
        s[i++] = '-';
        n = -n;
        }
    if (n / 10) {
        i = itoa(n / 10, s, i);
        }
    s[i++] = n % 10 + '0';
    s[i] = '\0';
    return i;
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
    //int i;
    char s[100];

    itoa(+1234, s, 0);
    printf ("%s\n", s);
    //printd(-1234);

    }
