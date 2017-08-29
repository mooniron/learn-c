/**************************************************************
* Name     :  ex5-13-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月11日
**************************************************************/



/*
exercise 5-13:
tail -n:
    write tail n lines
*/

#include <stdio.h>
#include <stdlib.h>

/*  max number of lines */
#define MAXLINES 1000   // end no ;
/*  pointer array to text lines  */
char *lines[MAXLINES];

int readlines(char *lines[], int maxlines);
void writelines(char *lines[], int linesno, int n);

/*  main function, default is entab, -d for detab  */
int main(int argc, char *argv[]) {
    int c, n, arguflag ;
    int linesno;

    arguflag = 0;
    n = 0;

    /*  tail -n  */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch(c) {
                case '0': case '1': case '2': case '3': case '4': case '5': case '6': \
                case '7': case '8': case '9':
                    arguflag = 1;
                    n = n * 10 + (c - '0');
                    break;
                default:
                    argc = 0;
                    printf("unknown command %c\n", *argv[0]);
                    break;
                }   //end switch
            }   //end while ((c =...
        }   //end while


    if (argc != 0) {
        printf("usage print tail n (n >= 0) lines : tail.exe -n\n");
        }
    else {
        /*  set default value n = 10  */
        if (arguflag == 0) {
            n = 10;
            }
        linesno = readlines(lines, MAXLINES);
        writelines(lines, linesno, n);
        }   //end if (argc != 1)

    }   //end function main



/*  writelines block  */
void writelines(char *lines[], int nlines, int n) {

    /*  set pointer lines to offset nlines -n  */
    if (nlines >= n) {
        lines += nlines - n;
        nlines = n;
        }


    while (nlines-- > 0) {
        printf("%s\n", *lines++);
        }   //end while

    }   //end function writelines



/*  tablines block  */
#define MAXLEN 1000

int getline(char *, int);
void strcpy(char *, char *);
char *alloc(int);
void afree(char *);

/*
    n : one tab to n spaces;
    deflag == 1: detab lines; else entab lines;
    return the total lines number;
*/
int readlines(char *lines[], int maxlines) {
    //  number of total lines
    int nlines;
    int len;
    char line[MAXLEN], *p;

    while ((len = getline(line, MAXLEN)) > 0) {

        /*  not enough spaces to store  */
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
            }
        else {
            line[len-1] = '\0';
            /*  why copy line to p  */
            strcpy(p, line);
            *lines++ = p;
            nlines++;
            }   //end if

        }   //end while

    return nlines;
    }   //end function readlines

/*  getline block  */
int getline(char *line, int maxlen) {
    int i = 0, c;

    while (i < maxlen - 1 && (c = getchar()) != EOF && c != '\n') {
        *line++ = c;
        i++;
        }   //end while

    if (c == '\n') {
        *line++ = '\n';
        i++;
        }   //end if
    *line = '\0';

    return i;
    }   //end function getline

/*  strcpy: copy t to s  */
void strcpy(char *s, char *t) {
    while ((*s++ = *t++) != '\0') {
        ;
        }
    }   //end function strcpy


/*  alloc block  */
#define ALLOCSIZE 100000
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
    }   //end function alloc

/*  afree: free storage to pointer p  */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
        }
    }
