/**************************************************************
* Name     :  ex7-6-2.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
example: line input and output

fgets: char *fgets(char *line, int maxline, FILE *fp);
    read the next input line (include '\n') from file fp into the character array line;
at most maxline-1 characters will be read. the resulting line is terminated with '\0'.
normally fgets returns line; on end of file or error it returns NULL.

fputs: int puts(char *line, FILE *fp);
    fputs writes a string (which need not contain a newline) to a file; it returns EOF if an
error occurs, and non-negative otherwise.

gets, puts: similar to fgets and fputs, but operate on stdin and stdout.
    confusingly, gets deletes the terminating '\n', and puts adds it.
*/


#include <stdio.h>
#include <stdlib.h>

/*  fgets: get at most n chars from iop  */
char *fgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n') {
            break;
            }   //end if
        }   //end while
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
    }   //end function fgets


/*  fputs: put string s on file iop  */
int fputs(char *s, FILE *iop) {
    int c;

    while (c = *s++) {
        putc(c, iop);
        }   //end while
    return ferror(iop) ? EOF : 0;
    }   //end function fputs


/*  getline: read a line, return length  */
int getline(char *line, int max) {
    if (fgets(line, max, stdin) == NULL) {
        return 0;
        }
    else {
        return strlen(line);
        }
    }   //end function getline

