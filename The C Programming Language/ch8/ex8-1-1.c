/**************************************************************
* Name     :  ex8-1-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月30日
**************************************************************/


/*
exercise 8-1:
    rewrite the program cat from Chapter 7 using read, write, open, and close instead of their
standard library equivalents. perform experiments to determine the relative speeds of the two
versions.

outline:
    1.  can only run on the UNIX system.
*/


/*
example: file access
fopen: return a file pointer, automatically call fclose when terminate normally.
    file pointer: points to a structure that contains information about the file, such as the
location of a buffer, the current character position in the buffer, whether the file is being
read or written, and whether errors or end of file have occurred.
    // FILE is a type name like int;
    FILE *fp;
    FILE *fopen(char *name, char *mode);
    fp = fopen(name, mode);
    modes include read ("r"), write ("w"), and append ("a"), binary files ("b").
fclose: break the connection between the file pointer and the external name, free file pointer.
    int fclose(FILE *fp);
freopen: reassigned

getc: return the next character from a file; return EOF for end of file or error.
    int getc(FILE *fp);
putc: write the character c to file fp and return character written, or EOF if error;
    int putc(int c, FILE *fp);
stdin, stdout, stderr: constants
    #define getchar() getc(stdin)
    #define putchar(c) putc((c), stdout)
fscanf, fprintf:
    int fscanf(FILE *fp, char *format, ...);
    int fprintf(FILE *fp, char *format, ...);


cat: concatenate a set of named files into the standard output.
    cat x.c y.c
*/


#include <stdio.h>
// for O_RDONLY
#include <fcntl.h>
// for exit(1)
#include <stdlib.h>

void error(char *, ...);

/*  cat: concatenate files, version 1  */
int main(int argc, char *argv[]) {
    // file descriptor
    int fdin = 0;
    // stdout file descriptor
    int fdout = 1;
    void ufilecopy(int, int);

    /*  no args: copy standard input  */
    if (argc == 1) {
        ufilecopy(fdin, fdout);
        }
    else {
        while(--argc > 0) {
            if ((fdin = open(*++argv, O_RDONLY, 0)) < 0) {
                error("cat: can't open %s", *argv);
                }
            else {
                ufilecopy(fdin, fdout);
                close(fdin);
                }
            }   //end while
        }   //end if

    return 0;
    }   //end function main

#define BUFSIZE 1024

/*  ufilecopy: copy file ifp to file ofp  */
void ufilecopy(int ifd, int ofd) {
    int n;
    //char buf[BUFSIZ];
    char buf[BUFSIZE];

    while ((n = read(ifd, buf, BUFSIZE)) > 0) {
        if (write(ofd, buf, n) != n) {
            error("write file error");
            }
        }
    }   //end function ufilecopy


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
