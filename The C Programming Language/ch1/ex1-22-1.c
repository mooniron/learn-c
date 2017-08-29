/**************************************************************
* Name     :  ex1-22-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月21日
**************************************************************/

/*  function: wrap line : derective method  */

#include <stdio.h>
/* the max col of output*/
#define MAXCOL 1000
/* the max line of output */
#define MAXLINE 1000
/* the max length of wrap line */
#define WRAPLEN 10

int getline(char line[], int maxlen);
int wrapline(char out[], char in[]);

int main(void) {
    int i;
    int count = 0;
    int outlines = 0;
    char line[MAXCOL];
    char output[MAXLINE][MAXCOL];

    for (i = 0; getline(line, MAXCOL) > 0; i++) {
        if (i < MAXLINE) {
            /*  the array argument give the address of firest item,
                and excute the function and modify the value of the array  */
            outlines += wrapline(output[i], line);
            }
        }
    /*  the total number of lines in output  */
    count = i;
    /* there was a line */
    if (count > 0) {
        printf("\n\nwrap line in %d lengs per line .\n\n", WRAPLEN);
        printf("the total lines of input is %d.\n", count);
        printf("the total lines of output is %d.\n", outlines);

        if (count <= MAXLINE) {
            printf("They are list below :\n\n");

            for (i = 0; i < count; ++i) {
                printf("%s", output[i]);
                }
            printf("\n");
            }
        else {
            printf("The limit number of lines to print is %d.\n", MAXLINE);
            printf("ah, there are too many lines to print. I are dying!!!\n");
            }
        }
    else {
        printf("\nERROR: NO INPUT\n");
        }

    return 0;

    }

/*  getline : read a line into s, return length of the line  */
int getline(char s[], int slim) {
    int c, i;

    for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        if (i < slim - 1) {
            s[i] = c;
            }
        }
    if (c == '\n') {
        // ingore the character after the limit length slim-2 .
        if (i < slim - 1) {
            s[i] = c;
            }
        i++;
        }
    if (i < slim) {
        s[i] = '\0';
        }
    else {
        // s[slim-1] is the last one of array s[slim].
        s[slim - 1] = '\0';
        }
    return i;
    }

/*  wrapline : intelligent line wrap. convert in[] to out[].
    the max length of out line is "WRAPLEN"  */
int wrapline(char out[], char in[]) {

    int i, j;
    /*  the index of temp */
    int itemp = 0;
    /*  the index of out */
    int iout = 0;
    /*  the number of out lines  */
    int outline = 0;
    /*  the last blank number befor WRAPLEN */
    int iblank = -1;
    /*  temp array store the WRAPLEN  */
    char temp[WRAPLEN];
    i = j = 0;
    for (i = 0; in[i] != '\0'; i++) {

        if (itemp < WRAPLEN) {
            temp[itemp] = in[i];
            // store the index of  the last blank or tab.
            if ((temp[itemp] == ' ') || (temp[itemp] == '\t')) {
                iblank = itemp;
                }
            itemp++;
            }
        else {
            // itemp == WRAPLEN, initialize itemp to 0.
            itemp = 0;
            // there is no blank in temp, current WRAPLEN length input
            if (iblank < 0) {
                for (j = 0; j < WRAPLEN; j++) {
                    out[iout++] = temp[j];
                    }
                // insert a '\n' in out.
                out[iout++] = '\n';
                outline++;
                // store the current in[i] in temp.
                temp[itemp++] = in[i];
                }
            // there is a blank in temp.
            else {
                for (j = 0; j < WRAPLEN; j++) {
                    if (j <= iblank) {
                        out[iout++] = temp[j];
                        }
                    else {
                        // store the char after the last blank, turn to next line.
                        temp[itemp++] = temp[j];
                        }
                    }
                out[iout++] = '\n';
                outline++;
                // store the in to temp
                temp[itemp++] = in[i];
                }
            iblank = -1;
            }
        }
    /*  temp[] : the string length < WRAPLEN, store in temp[], before '\0',
        copy temp to out.  the last line so far  */
    for (j = 0; j < itemp; j++) {
        out[iout++] = temp[j];
        }
    outline++;
    // the end flag '\0'
    out[iout] = '\0';
    return outline;
    }

void strcomb(char begin[], char end[]) {
    int i,j;
    for (i = 0; begin[i] != '\0'; i++) {
        ;
        }
    for (j = 0; end[j] != '\0'; j++) {
        begin[i++] = end[j];
        }
    begin[i] = '\0';
    }
