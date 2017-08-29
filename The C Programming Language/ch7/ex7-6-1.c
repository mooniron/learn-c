/**************************************************************
* Name     :  ex7-6-1.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
exercise 7-6:
    write a program to compare two files, printing the first line where they differ.

outline:
*/



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
#include <string.h>

// max length of a line
#define MAXLEN 1000

/*  main block  */
int main(int argc, char *argv[]) {
    // two file pointer to two compare files
    FILE *fp1, *fp2;
    // two file names
    char *name1, *name2;
    // two compare lines
    char line1[MAXLEN], line2[MAXLEN];

    // illegal command line
    if (argc != 3) {
        fprintf(stderr, "error: command line.\nusage: compare.exe file1 file2\n");
        exit(3);
        }   // end if argc

    name1 = argv[1];
    name2 = argv[2];

    // open files error
    if ((fp1 = fopen(name1, "r")) == NULL) {
        fprintf(stderr, "error: can't open %s\n", name1);
        // first file open error
        exit(1);
        }   //end if fp1

    // open files error
    if ((fp2 = fopen(name2, "r")) == NULL) {
        fprintf(stderr, "error: can't open %s\n", name2);
        // first file open error
        exit(1);
        }   //end if fp1

    while (fgets(line1, MAXLEN, fp1) != NULL) {
        if (fgets(line2, MAXLEN, fp2) == NULL) {
            printf("file %s is larger than file %s\n", name1, name2);
            printf("they are same before file %s is end\n", name2);
            printf("%s: %s\n", name1, line1);
            exit(0);
            }
        else if (strcmp(line1, line2) != 0) {
            printf("the first different line in two files are:\n\n");
            printf("%s: %s\n", name1, line1);
            printf("%s: %s\n", name2, line2);
            exit(0);
            }
        }

    if (fgets(line2, MAXLEN, fp2) == NULL) {
        printf("the file %s and file %s are match completely\n", name1, name2);
        }
    else {
        printf("file %s is larger than file %s\n", name2, name1);
        printf("they are same before file %s is end\n", name1);
        printf("%s: %s\n", name2, line2);
        }

    exit(0);
    }   //end function main
