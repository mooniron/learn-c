/**************************************************************
* Name     :  ex7-5-3.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月25日
**************************************************************/


/*
version 0.2:
    revise cat to write its error messages on the standard error.

exit: exit(expr);
    0 signals that all is well; non-zero values usually signal abnormal situations.
exit calls fclose for each open output file, to flush out any buffer output.
    exit has the advantage that it can be called from other functions, and that calls to it
can be found with a pattern-searching program like those in chapter 5.

ferror return non-zero if an error occurred on the stream fp;
    int ferror(FILE *fp);

feof: it returns non-zero if end of EOF has occurred on the specified file.
    int feof(FILE *fp):
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
// for exit(int);
#include <stdlib.h>


/*  cat: concatenate files, version 2  */
int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);
    /*  program name for errors  */
    char *prog = argv[0];

    /*  no args: copy standard input  */
    if (argc == 1) {
        filecopy(stdin, stdout);
        }
    else {
        while(--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: cat: can't open %s\n", prog, *argv);
                exit(1);
                //return 1;
                }
            else {
                filecopy(fp, stdout);
                fclose(fp);
                }
            }   //end while
        // ferror return non-zero if an error occurred on stdout
        if (ferror(stdout)) {
            fprintf(stderr, "%s: error writing stdout\n", prog);
            exit(2);
            }
        }   //end if

    exit(0);
    }   //end function main


/*  filecopy: copy file ifp to file ofp  */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        }
    }   //end function filecopy
