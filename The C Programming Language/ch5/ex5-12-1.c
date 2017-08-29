/**************************************************************
* Name     :  ex5-12-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月11日
**************************************************************/

/*
exercise 5-12:
add -n +m optinal argument for entab and detab.
-n stop at column n.
+m start at column m.
n = -1 for default, stop at the end of the line.
m = -1 for default, start at the begin of the line.
*/

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

int tablines(char *lines[], int maxlines, int tabspace, int deflag, int start, int stop);
void writelines(char *lines[], int linesno);

/*  main function, default is entab, -d for detab  */
int main(int argc, char *argv[]) {
    int c;
    /* deflag = 1 for detab, 0 for entab  */
    int deflag;
    /*  stop @ end  */
    int n = 0;
    /*  start @ begin  */
    int m = 0;
    int stopflag = 0;
    int startflag = 0;
    /*  total number of lines  */
    int linesno = 0;

    deflag = 0;
    //endeflag = 0;

    /*  exe +d3 tabspace  */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch(c) {
                case 'd':
                    deflag = 1;
                    break;
                case '0': case '1': case '2': case '3': case '4': case '5': case '6': \
                case '7': case '8': case '9':
                    stopflag = 1;
                    n = n * 10 + (c - '0');
                    break;
                default:
                    argc = 0;
                    printf("unknown command %c\n", *argv[0]);
                    break;
                }   //end switch
            }   //end while ((c = ...
        }   //end while (--argc > 0...


    /*  exe +d3 tabspace  */
    while ((*argv)[0] == '+' && argc-- > 0) {
        while ((c = *++argv[0]) != '\0') {
            switch(c) {
                case 'd':
                    deflag = 1;
                    break;
                case '0': case '1': case '2': case '3': case '4': case '5': case '6': \
                case '7': case '8': case '9':
                    startflag = 1;
                    m = m * 10 + (c - '0');
                    break;
                default:
                    argc = 0;
                    printf("unknown command %c\n", *argv[0]);
                    break;
                }   //end switch
            }   //end while ((c = ...
        argv++;
        }   //end while (--argc > 0...

    /*  set default value  */
    if (startflag == 0) {
        m = -1;
        }
    if (stopflag == 0) {
        n = -1;
        }

    if (argc != 1) {
        linesno = tablines(lines, MAXLINES, 4, 0, 0, 0);
        writelines(lines, linesno);
        printf("usage tablines/entablines: main.exe -d +1 -3 tabspace\n");
        }
    else {
        linesno = tablines(lines, MAXLINES, atoi(*argv), deflag, m, n);
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
int detabline(char *, char *, int, int, int, int);
int entabline(char *, char *, int, int, int, int);
void strcpy(char *, char *);
char *alloc(int);
void afree(char *);

/*
    n : one tab to n spaces;
    deflag == 1: detab lines; else entab lines;
    return the total lines number;
    start: start @ m column
    stop: stop @ n column
*/
int tablines(char *lines[], int maxlines, int tabspace, int deflag, int start, int stop) {
    //  number of total lines
    int nlines;
    int len;
    char line[MAXLEN], *outline, *p;

    while ((len = getline(line, MAXLEN)) > 0) {
        /*  deflag == 1, detab line; else entab line  */
        if (deflag == 1) {
            /*  request len * tabspace room for detab  */
            if ((outline = alloc(len * tabspace)) == NULL) {
                return -1;
                }
            else {
                len = detabline(line, outline, tabspace, len, start, stop);
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
                len = entabline(line, outline, tabspace, len, start, stop);
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
int detabline(char *s, char *t, int tabspace, int slen, int start, int stop) {
    int i, len = 0;
    char *beginp = s, *endp = s;

    /*  initial beginp */
    if (start > 0 && start <= slen) {
        beginp = s + start - 1;
        }
    else if (start > slen) {
        beginp = s + slen;
        }
    else {
        beginp = s;
        }

    /*  initial endp  */
    if (stop > 0 && stop <= slen ) {
        endp = s + stop;
        }
    else if (stop == 0) {
        //endp = NULL;
        endp = s;
        }
    else {
        endp = s + slen;
        }

    /*  from s to beginp, copy s to t  */
    while (s < beginp && *s != '\0') {
        *t++ = *s++;
        len++;
        }

    /*  from beginp to endp, detab  */
    while (s >= beginp && s < endp && *s != '\0') {
        if (*s == '\t') {
            for (i = 0; i < tabspace; i++) {
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

    /*  from endp to s == '\0', copy s to t  */
    while (s >= endp && *s != '\0') {
        *t++ = *s++;
        len++;
        }

    *t = '\0';

    return len;
    }   //end function detabline

int entabline(char *s, char *t, int tabspace, int slen, int start, int stop) {
    int i, ispace, len = 0;
    char *beginp = s, *endp = s + slen;

    ispace = 0;

    /*  initial beginp */
    if (start > 0 && start <= slen) {
        beginp = s + start - 1;
        }
    else if (start > slen) {
        beginp = s + slen;
        }
    else {
        beginp = s;
        }

    /*  initial endp  */
    if (stop > 0 && stop <= slen ) {
        endp = s + stop;
        }
    else if (stop == 0) {
        //endp = NULL;
        endp = s;
        }
    else {
        endp = s + slen;
        }


    /*  from s to beginp, copy s to t  */
    while (s < beginp && *s != '\0') {
        *t++ = *s++;
        len++;
        }

    /*  from beginp to endp, entab  */
    while (s < endp && *s != '\0') {

        if (*s == ' ') {
            ispace++;
            s++;
            }
        else {
            /*  tabspace spaces to one tab  */
            for (i = 0; i < ispace / tabspace; i++) {
                *t++ = '\t';
                len++;
                }
            /*  left spaces  */
            for (i = 0; i < ispace % tabspace; i++) {
                *t++ = ' ';
                len++;
                }

            //initialize ispace
            ispace = 0;
            *t++ = *s++;
            len++;
            }   //end if
        }   //end while

    /*  from endp to s == '\0', copy s to t  */
    while (*s != '\0') {
        *t++ = *s++;
        len++;
        }

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
