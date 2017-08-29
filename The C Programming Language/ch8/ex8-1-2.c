/**************************************************************
* Name     :  ex8-1-2.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
example: input and output in UNIX

file descriptor:
    0 for input, 1 for output, and 2 for error output. file assignment is done by shell.
    when shell run a program, open three files, 0 for stdin, 1 for stdout, 2 for stderr.

system call:
read: return a count of the number of bytes transferred.
    // fd: file descriptor; return 0 for EOF, -1 if an error.
    int n_read = read(fd, char *buf, int n);
write: an error occured if written isn't equal to the number requested.
    int n_written = write(int fd, char *buf, int n);
*/


#include "syscalls.h"

/*  copy input to output  */
int main() {
    // BUFSIZ is defined in syscalls.h
    char buf[BUFSIZ];
    int n;

    while ((n = read(0, buf, BUFSIZ)) > 0) {
        write(1, buf, n);
        }   //end while
    }   //end function main


/*  getchar: unbuffered single character input  */
int getchar(void) {
    char c;

    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
    }   //end function getchar


/*  getchar: simple buffered version  */
int getcharbuf(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    /*  buffer is empty  */
    if (n == 0) {
        n = read(0, buf, sizeof buf);
        bufp = buf;
        }

    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
    }   //end function getcharbuf
