/**************************************************************
* Name     :  ex5-7-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercise 5-7:
    Rewrite readlines to store lines in an array supplied by main ,
    rather than calling alloc to maintain storage. How much faster is the program?
*/

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
/*  max length of any input lines  */
#define MAXLEN 1000


/*  read all lines, return number of lines  */
int readlines(char lines[][MAXLEN], int maxlines);
/*  print lines  */
void writelines(char lines[][MAXLEN], int nlines);

char lines[MAXLINES][MAXLEN];

/*  main function  */
int main(void) {
    /*  number of input lines read  */
    int nlines;


    if ((nlines = readlines(lines, MAXLINES)) >= 0) {
        //qsort(lines, 0, nlines - 1);
        writelines(lines, nlines);
        return 0;
        }
    else {
        printf("error: input too big to sort\n");
        return 1;
        }

    //return 0;
    }




int getline(char *, int);
char *alloc(int);

/*  readlines: read input lines  */
int readlines(char lines[][MAXLEN], int maxlines) {
    int len, nlines;

    nlines = 0;
    while ((len = getline(lines[nlines], MAXLEN)) > 0) {
        /*  nlines too big or memory full  */
        if (nlines >= maxlines) {
            return -1;
            }
        else {
            /*  delete newline '\n', allocated memory of each line is len  */
            lines[nlines++][len-1] = '\0';
            }
        }

    return nlines;
    }

/*  writelines: write outputlines  */
void writelines(char lines[][MAXLEN], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
    printf("%s\n", lines[i]);
        //printf("%s\n", lineptr[i]);
        }
    }

int getline(char line[], int maxlen) {
    int c, len;

    len = 0;
    while (len < maxlen - 1 && (c = getchar()) != EOF && c != '\n') {
        line[len] = c;
        len++;
        }

    //if (len < maxlen - 1 && c == '\n') {
    if (c == '\n') {
        line[len] = c;
        len++;
        }

    line[len] = '\0';

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



