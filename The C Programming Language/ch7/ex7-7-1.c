/**************************************************************
* Name     :  ex7-7-1.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
exercise 7-7:
    modify the pattern finding program of chapter 5 to take its input from a set of named files,
or if no files are named as arguments, from the standard input. should the file name be printed
when a matching line is found?

outline: exe pattern file1, file2, ...
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define MAXLEN 1000

char *findpattern(char *, char *);
void filecopy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    FILE *fp, *stdtemp;
    int found;
    char line[MAXLEN], *word, temp[] = "temp.txt";

    found = 0;

    // error usage command line
    if (argc == 1) {
        fprintf(stderr, "usage: gep.exe pattern (optional file names)\n");
        exit(-1);
        }
    // no input file names, use stdin
    else if (argc == 2) {
        // pattern word
        word = argv[1];
        // creat temp file
        if ((stdtemp = fopen(temp, "w")) == NULL) {
            fprintf(stderr, "error: to creat file %s\n", temp);
            exit(1);
            }
        // output title
        fputs("file: standard input stdin\n", stdtemp);
        while((fgets(line, MAXLEN, stdin)) != NULL) {
            // found pattern
            if (findpattern(line, word) != NULL) {
                found++;
                fputs(line, stdtemp);
                }   //end if pattern
            }   //end while
        // save and close file
        fclose(stdtemp);
        stdtemp = fopen(temp, "r");
        // stdout output
        if (found > 0) {
            filecopy(stdtemp, stdout);
            }
        if (ferror(stdout)) {
            fprintf(stderr, "error, write stdout\n");
            exit(1);
            }
        fclose(stdtemp);
        }   //end if argc == 2
    // argc >= 3, input files
    else {
        // pattern word
        word = *++argv;
        // skip first two arguments in command line
        argc -= 2;
        //argv += 2;
        while (argc-- > 0) {
            // open file error
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "error: to open file %s\n", *argv);
                exit(1);
                }
            // open file sucess
            else {
                // print title file name
                printf("file: %s\n", *argv);
                while (fgets(line, MAXLEN, fp) != NULL) {
                    if (findpattern(line, word) != NULL) {
                        found++;
                        printf("%s", line);
                        }
                    }   //end while fgets line
                //close file
                fclose(fp);
                printf("\n");
                }
            }   //end if fp
        }   //end argc >= 3;

    exit(0);
    }   //end function main


/*  findpattern: */
char *findpattern(char *s, char *t) {
    char *temp, *tempt = t;

    for (temp = s; *s != '\0'; s++) {
        t = tempt;
        if (*t == *s) {
            for (temp = s;*t != '\0' && *temp == *t; temp++, t++) {
                ;
                }
            if (*t == '\0') {
                return s;
                }
            }
        }   //end for

    // not found
    return NULL;
    }   //end function findpattern


/*  filecopy: copy ifp to ofp  */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        }   //end while
    }   //end function filecopy
