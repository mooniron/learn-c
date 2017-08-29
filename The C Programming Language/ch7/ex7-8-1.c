/**************************************************************
* Name     :  ex7-8-1.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
exercise 7-8:
    write a program to print a set of files, starting each new one on a new page, with a title
and a running page count for each file.
*/


#include <stdio.h>

void filecopy(FILE *, FILE *);

/*  main block  */
int main(int argc, char *argv[]) {
    int count;
    FILE *fp;

    count = 0;

    // no arguments
    if (argc == 1) {
        fprintf(stderr, "usage: exe filename ...\n");
        return -1;
        }

    //
    while (--argc > 0) {
        // error open file
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "can not open file %s\n", *argv);
            return 1;
            }
        else {
            //printf title filename
            printf("    %s\n", *argv);
            filecopy(fp, stdout);
            fclose(fp);
            count++;
            printf("    %d\n", count);
            }
        }   //end while --argc

    return 0;
    }   //end function main


/*  filecopy: copy ifp to ofp  */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        }   //end while
    }   //end function filecopy

