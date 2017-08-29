/**************************************************************
* Name     :  ex8-2-2.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月30日
**************************************************************/


/*
example: random access - lseek (file access)

fseek: standard library version, the first argument is FILE * and the return is non-zero if an
error occurred.

lseek: return the new position in the file, or -1 if an error occurs. with slower access.
    long lseek(int fd, long offset, int origin);
    offset is taken relative to the location by origin. origin can be 0, 1, or 2 to specify that
offset is to be measured from the beginning, from the current position, or from the end of file.
    // append a file
    lseek(fd, 0L, 2);
    // rewind to beginning
    lseek(fd, 0L, 0);
*/


#include "syscalls.h"

/*  get: read n bytes from position pos  */
int get(int fd, long pos, char *buf, int n) {
    if (lseek(fd, pos, 0) >= 0) {
        return (read(fd, buf, n));
        }
    else {
        return -1;
        }
    }   //end function get
