/**************************************************************
* Name     :  ex5-7-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
example: pointer array and pointers to pointers
1.sort lines:
outline:
    read all the lines of input;
    sort them;
    print them in order;

*/

#include <stdio.h>
#include <string.h>

/*  max #lines to be sorted  */
#define MAXLINES 5000

/*  pointer array to text lines  */
char *lineptr[MAXLINES];

/*  read all lines, return number of lines  */
int readlines(char *lineptr[], int maxlines);
/*  print lines  */
void writelines(char *lineptr[], int nlines);
/*  sort input lines  */
void qsort(char *lineptr[], int left, int right);

/*  main function  */
int main(void) {
    /*  number of input lines read  */
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
        }
    else {
        printf("error: input too big to sort\n");
        return 1;
        }

    //return 0;
    }


/*  max length of any input lines  */
#define MAXLEN 1000

int getline(char *, int);
char *alloc(int);

/*  readlines: read input lines  */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        /*  nlines too big or memory full  */
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
            }
        else {
            /*  delete newline '\n', allocated memory of each line is len  */
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            }
        }

    return nlines;
    }

/*  writelines: write outputlines  */
void writelines(char *lineptr[], int nlines) {
    //int i;

    //for (i = 0; i < nlines; i++) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
        //printf("%s\n", lineptr[i]);
        }
    }

int getline(char *line, int maxlen) {
    int c, len;

    len = 0;
    while (len < maxlen - 1 && (c = getchar()) != EOF && c != '\n') {
        *line++ = c;
        len++;
        }

    //if (len < maxlen - 1 && c == '\n') {
    if (c == '\n') {
        *line++ = c;
        len++;
        }

    *line = '\0';

    return len;
    }

/*  available memory for lines storage  */
#define ALLOCSIZE 10000
/*  storage for alloc, visible only for alloc and afree  */
static char allocbuf[ALLOCSIZE];
/*  next free position pointer, the array name is the address of the zeroth element  */
static char *allocp = allocbuf;

/*  alloc: return pointer to n characters  */
char *alloc(int n) {
    /*  it fits  */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        /*  old p  */
        return allocp - n;
        }
    /*  not enough room  */
    else {
        /*  zero is illegal address  */
        return 0;
        }
    }

/*  afree: free storage pointed to p  */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
        }
    }



/*  qsort: sort v[left]...v[right] into increasing order  */
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    /*  do nothing if array contains fewer than two elements  */
    if (left >= right) {
        return;
        }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        /*  *v[i] < *v[left], */
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
            }
        }
    swap(v, left, last);

    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
    }

/*  swap: interchange the i and j element in pointer array  */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;

    }
