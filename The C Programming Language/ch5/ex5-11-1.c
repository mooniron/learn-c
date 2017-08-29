/**************************************************************
* Name     :  ex5-11-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月11日
**************************************************************/

/*
exercise 5-11:
tablines, entablines: command-line arguments verssion
include memory allocator test.
*/

#include <stdio.h>
#include <stdlib.h>

/*  max number of lines */
#define MAXLINES 1000   // end no ;
/*  pointer array to text lines  */
char *lines[MAXLINES];

int tablines(char *lines[], int maxlines, int tabspace, int deflag);
void writelines(char *lines[], int linesno);

/*  main function, default is entab, -d for detab  */
int main(int argc, char *argv[]) {
    int deflag;
    int linesno;

    deflag = 0;
    //endeflag = 0;

    /*  exe -d tabspace  */
    while (--argc > 0 && (*++argv)[0] == '-') {
        switch(*++argv[0]) {
            case 'd':
                deflag = 1;
                break;
            /*case 'e':
                endeflag = 1;
                break;*/
            default:
                argc = 0;
                printf("unknown command %c\n", *argv[0]);
                break;
            }   //end switch
        }   //end while

    if (argc != 1) {
        printf("usage tablines/entablines: main.exe -d tabspace\n");
        }
    else {
        linesno = tablines(lines, MAXLINES, atoi(*argv), deflag);
        writelines(lines, linesno);
        }   //end if (argc != 1)

    }   //end function main



/*  writelines block  */
void writelines(char *lines[], int nlines) {

    while (nlines-- > 0) {
        printf("%s\n", *lines++);
        }   //end while

    }   //end function writelines



/*  tablines block  */
#define MAXLEN 1000

int getline(char *, int);
int detabline(char *, char *, int);
int entabline(char *, char *, int);
void strcpy(char *, char *);
char *alloc(int);
void afree(char *);

/*
    n : one tab to n spaces;
    deflag == 1: detab lines; else entab lines;
    return the total lines number;
*/
int tablines(char *lines[], int maxlines, int n, int deflag) {
    //  number of total lines
    int nlines;
    int len;
    char line[MAXLEN], *outline, *p;

    while ((len = getline(line, MAXLEN)) > 0) {
        /*  deflag == 1, detab line; else entab line  */
        if (deflag == 1) {
            /*  request len * n room for detab  */
            if ((outline = alloc(len * n)) == NULL) {
                return -1;
                }
            else {
                len = detabline(line, outline, n);
                afree(outline);
                }

            //printf ("%d\n", len);
            }
        else {
            /*  request len room for entab  */
            if ((outline = alloc(len)) == NULL) {
                return -1;
                }
            else {
                len = entabline(line, outline, n);
                afree(outline);
                }
            }   //end if

        /*  not enough spaces to store  */
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
            }
        else {
            outline[len-1] = '\0';
            /*  why copy line to p  */
            strcpy(p, outline);
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


/*  detabline: convert a tab to n spaces of a line, return the length of new line  */
int detabline(char *s, char *t, int n) {
    int i, len = 0;

    while (*s != '\0') {
        if (*s == '\t') {
            for (i = 0; i < n; i++) {
                *t++ = ' ';
                len++;
                }   //end for
            s++;
            }
        else {
            *t++ = *s++;
            len++;
            }   //end if
        }   //end while

    *t = '\0';

    return len;
    }   //end function detabline

int entabline(char *s, char *t, int n) {
    int i, ispace, len = 0;

    ispace = 0;
    while (*s != '\0') {
        if (*s == ' ') {
            ispace++;
            s++;
            }
        else {
            /*  n spaces to one tab  */
            for (i = 0; i < ispace / n; i++) {
                *t++ = '\t';
                len++;
                }
            /*  left spaces  */
            for (i = 0; i < ispace % n; i++) {
                *t++ = ' ';
                len++;
                }
            //initialize ispace
            ispace = 0;
            *t++ = *s++;
            len++;
            }   //end if
        }   //end while

    *t = '\0';

    return len;
    }   //end function entab


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
