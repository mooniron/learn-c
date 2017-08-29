/**************************************************************
* Name     :  ex5-14-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月11日
**************************************************************/


/*
exercise 5-14:
modify the sort program to handle a -r flag,
which indicates sorting in reverse (decreasing) order.
*/

/*
example: pointer to function
quick sort:
    numerical, and lexicographic
    numcmp: compare two lines on the basis of numeric value.
    int (*comp)(void *, void *) is a pointer to a function, the function return a int.
    int *comp(void *, void *) is a function return a int *.
*/

#include <stdio.h>
#include <string.h>
/*  max #lines to be sorted  */
#define MAXLINES 5000
/*  pointers to text lines  */
char *lineptr[MAXLINES];
/*  false: increasing, true: decreasing  */
int reverse = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *));
int numcmp(char *, char *);
int strcmpr(char *, char *);

/*  sort input lines  */
int main(int argc, char *argv[]) {
    /*  number of input lines read  */
    int nlines;
    /*  1 if numeric sort  */
    int numeric = 0;
    int c = 0;

    /*  argument begin with '-'  */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch(c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default:
                    argc = 0;
                    printf("unknown command %c\n", c);
                    break;
                }   //end switch
            }   //end while ((c =
        }   //end while (--argc > 0

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void**) lineptr, 0, nlines-1, (int (*)(void *, void *)) (numeric ? numcmp : strcmpr));
        writelines(lineptr, nlines);
        return 0;
        }
    else {
        printf("input too big to sort\n");
        return 1;
        }   //end if ((nlines ...

    }   //end function main


/*  qort: sort v[left]...v[right] into increasing order  */
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;

    void swap(void *v[], int, int);

    /*  do nothing if array contains fewer than two elements  */
    if (left >= right) {
        return;
        }   //end if (left...)

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
            }   //end if
        }   //end for
    swap(v, left, last);

    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);

    }   //end function qsort

/*  strcmpr: add reverse to strcmp  */
int strcmpr(char *s1, char *s2) {
    char *p1 = reverse ? s2 : s1;
    char *p2 = reverse ? s1 : s2;

    while (*p1 == *p2) {
        if (*p1 == '\0') {
            return 0;
            }
        p1++;
        p2++;
        }

    return *p1 - *p2;
    }


/*  numcmp block  */
#include <stdlib.h>

/*  numcmp: compare s1 and s2 numerically  */
int numcmp(char *s1, char *s2) {
    char *p1 = reverse ? s2 : s1;
    char *p2 = reverse ? s1 : s2;
    double v1, v2;

    v1 = atof(p1);
    v2 = atof(p2);

    if (v1 < v2) {
        return -1;
        }
    else if (v1 > v2) {
        return 1;
        }
    else {
        return 0;
        }   //end if

    }   //end function numcmp

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    }   //end function swap


/*  writelines: write lines  */
void writelines(char *lineptr[], int linenum) {
    while (linenum-- > 0) {
        printf("%s\n", *lineptr++);
        }   //end while
    }   //end function writelines


/*  readlines block  */
#define MAXLEN 1000

int getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
    int linesnum, len;
    char line[MAXLEN], *p;

    linesnum = len = 0;
    while ((len = getline(line, MAXLEN)) > 0) {

        if (linesnum >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
            }
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            *lineptr++ = p;
            linesnum++;
            }   //end if
        }   //END WHILE

    return linesnum;
    }   //end function readlines

int getline(char *s, int maxlen) {
    int i, c;

    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        *s++ = c;
        }   //end for
    if (c == '\n') {
        *s++ = c;
        i++;
        }
    *s = '\0';

    return i;
    }

/*  alloc block  */
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
        }
    else {
        return NULL;
        }
    }

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
        }
    }
