/**************************************************************
* Name     :  ex8-1-2.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
example: open, creat, close, unlink;

open: like fopen, just return a file descriptor, return -1 if any error occurs. if open non-exist
file, an error will occur. there is a limit (often about 20) on the number of files that a
program my open simultaneously.
    // file descriptor
    int fd;
    int open(char *name, int flags, int perms);
    fd = open(name, flags, perms);
    // open for read
    fd = open(name, 0_RDONLY, 0);
// flags constants are defined in <fcntl.h> on system V UNIX, and in <sys/file.h> on BSD.
    O_RDONLY    open for reading only;
    O_WRONLY    open for writing only
    O_RDWR      open for both reading and writing;

creat: return a file descriptor if it was able to creat the file, and -1 if not. if the file
already exists, creat will truncate it to zero length.
    int creat(char *name, int perms);
    fd = creat(name, perms);
    if the file does not already exist, creat creates it with the permissions specified by the
perms argument.

close: it corresponds to fclose except that there is no buffer flush. exit or return from the
main program closes all open files.
    close(int fd);

unlink: remove the file name from the file system. it corresponds to the standard library
function remove.
    unlink(char *name);
*/


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "syscalls.h"

/*  RW for owner, group, others  */
#define PERMS 0666

void error(char *, ...);

/*  cp: copy f1 to f2  */
int main(int argc, char *argv[]) {
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3) {
        error("Usage: cp from to");
        }
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1) {
        error("cp: can't open %s", argv[1]);
        }   //end if f1
    if ((f2 = creat(argv[2], PERMS)) == -1) {
        error("cp: can't creat %s mode %03o", argv[2], PERMS);
        }   //end if f2

    while ((n = read(f1, buf, BUFSIZ)) > 0) {
        if (write(f2, buf, n) != n) {
            error("cp: write error on file %s", argv[2]);
            }   //end if write
        }   //end while

    return 0;
    }   //end function main


#include <stdio.h>
#include <stdarg.h>

/*  error: print an error message and die  */
void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
    }   //end function error
