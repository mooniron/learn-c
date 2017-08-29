/**************************************************************
* Name     :  ex8-2-1.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月30日
**************************************************************/


/*
exercise 8-2:
    rewrite fopen and _fillbuf with fields instead of explicit bit operations.
    compare code size and execution speed.
*/


/*
example: an implementation of fopen and getc;
    A file pointer is a pointer to a structure that contains several pieces of information about
the file: a pointer to a buffer, so the file can be read in large chunks; a count of the number
of  characters left in the buffer; a pointer to the next character position in the buffer; the
file descriptor; and flags describing read/write mode, error status, etc.

*/


#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
// max #files open at once
#define OPEN_MAX 20
typedef struct _iobuf {
    // characters left
    int cnt;
    // next character position
    char *ptr;
    // location of buffer
    char *base;
    // mode of file access
    //int flag;
    // bit field flags
    struct {
        // file open for reading
        unsigned int _READ : 1;
        // file open for writing
        unsigned int _WRITE : 1;
        // file is unbuffered
        unsigned int _UNBUF : 1;
        // EOF occurred on this file
        unsigned int _EOF : 1;
        // error occurred on this file
        unsigned int _ERR : 1;
    } flag;
    // file descriptor
    int fd;
    } FILE;


enum _flags {
    // file open for reading
    _READ = 01,
    // file open for writing
    _WRITE = 02,
    // file is unbuffered
    _UNBUF = 04,
    // EOF has occurred on this file
    _EOF = 010,
    // error occurred on this file
    _ERR = 020
    };

// declare
extern FILE _iob[OPEN_MAX] ;
// definition and initializetion
FILE _iob[OPEN_MAX] = {
    // stdin
    {0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
    // stdout
    {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 1},
    // stderr
    {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2}
    };

// standard input file
#define stdin (&_iob[0])
// standard output file
#define stdout (&_iob[1])
// standard error file
#define stderr (&_iob[2])


int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag._EOF) != 0)
#define ferror(p) (((p)->flag._ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
    ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 \
    ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)


#include <fcntl.h>
//#include <stdio.h>
//#include "syscalls.h"
/*  RW for owner, group, others */
#define PERMS 0666

FILE *fopen(char *, char *);

/*  main test block  */
int main(int argc, char *argv[]) {
    FILE *fp;
    char c;

    if (argc == 1) {
        putchar('?');
        putchar('1');
        }
    else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            putchar('?');
            putchar('?');
            putchar('\n');
            }
        else {
            c = getc(fp);
            putchar(c);
            putchar('?');
            putchar('\n');
            }
        }
    return 0;
    }   //end function main

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    // error mode
    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
        }   // end if *mode

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        //found free slot
        if ((fp->flag._READ == 0) && (fp->flag._WRITE == 0 )) {
            break;
            }
        }   //end for fp
    // no free slots
    if (fp >= _iob + OPEN_MAX) {
        return NULL;
        }   //end if

    /*  creat fd block  */
    if (*mode == 'w') {
        fd = creat(name, PERMS);
        }
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0) == -1)) {
            fd = creat(name, PERMS);
            }
        lseek(fd, 0L, 2);
        }
    else {
        fd = open(name, O_RDONLY, 0);
        }
    // couldn't access name
    if (fd == -1) {
        return NULL;
        }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flag._READ = 1;
        fp->flag._WRITE = 0;
        }
    else {
        fp->flag._READ = 0;
        fp->flag._WRITE= 1;
        }
    fp->flag._UNBUF = 0;
    fp->flag._EOF = 0;
    fp->flag._ERR = 0;
    //fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
    }   //end function fopen


//#include "syscalls.h"
#include <stdlib.h>

/*  _fillbuf: allocate and fill input buffer  */
int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag._READ == 0) || (fp->flag._EOF == 1) || (fp->flag._ERR == 1)) {
        return EOF;
        }   //end if fp->flag

    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ;
    // no buffer yet
    if (fp->base == NULL) {
        // can't get buffer
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
            }
        }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    // eof or error
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag._EOF = 1;
            }
        else {
            fp->flag._ERR = 1;
            }
        fp->cnt = 0;
        return EOF;
        }   //end if (--fp->cnt < 0)
    return (unsigned char) *fp->ptr++;
    }   //end function _fillbuf


/*  _flushbuf: */
int _flushbuf(int c, FILE *fp) {
    int bufsize = 0;

    // read file flag, clear buffer
    if (fp->flag._READ == 1) {
        free((void *) fp->base);
        fp->base = NULL;
        fp->ptr = NULL;
        fp->cnt = 0;
        return 0;
        }

    /*   write  block  */
    // eof or error
    if ((fp->flag._WRITE== 0) || (fp->flag._EOF == 1) || (fp->flag._ERR == 1)) {
        return EOF;
        }
    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ;
    // no buffer yet
    if (fp->base == NULL) {
        // can't get buffer
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
            }
        }
    // error occurred when writing full buffer to file fp
    else if (bufsize > 1) {
        if (write(fp->fd, fp->base, bufsize - fp->cnt) != (bufsize - fp->cnt)) {
            fp->flag._ERR = 1;
            return EOF;
            }
        }
    // initialize ptr to buf[0];
    fp->ptr = fp->base;
    fp->cnt = bufsize;

    // EOF or some error
    if (c < 0) {
        free((void *) fp->base);
        fp->base = NULL;
        fp->ptr = NULL;
        fp->cnt = 0;
        return c;
        }

    // write character c to buffer, point to next position
    *fp->ptr = c;

    if (bufsize == 1) {
        // write error
        if (write(fp->fd, fp->ptr, 1) != 1) {
            fp->flag._ERR = 1;
            fp->cnt = 0;
            return EOF;
            }
        }

    fp->cnt--;
    return (unsigned char) *fp->ptr++;
    }   //end function _flushbuf
