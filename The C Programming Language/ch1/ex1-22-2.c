/**************************************************************
* Name     :  ex1-22-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月22日
**************************************************************/

/*  function: wrap line : recursive method  */

#include <stdio.h>
/* the max col of output*/
#define MAXCOL 1000
/* the max line of output */
#define MAXLINE 1000
/* the max length of wrap line */
#define WRAPLEN 10

int getline(char line[], int maxlen);
/*  out[] : the output array, outlen : the length of output seen so for,
    in[] : the input char array  */
void wrapline(char out[], int outlen, char in[]);

int main(void) {
    int i;
    int count = 0;

    char line[MAXCOL];
    char output[MAXLINE][MAXCOL];

    for (i = 0; getline(line, MAXCOL) > 0; i++) {
        if (i < MAXLINE) {
            wrapline(output[i], 0, line);
            }
        }
    /*  the total number of lines in output  */
    count = i;
    /* there was a line */
    if (count > 0) {
        printf("\n\nwrap line in %d length per line .\n\n", WRAPLEN);
        printf("the total lines of input is %d.\n", count);

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
        printf("ERROR: NO INPUT\n");
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

void wrapline(char out[], int oldoutlen, char in[]) {

    int i, j = 0;
    /*  the length of in */
    int inlen = 0;
    /*  the index of out */
    int iout = oldoutlen;
    int ilast = 0;
    /*  the last blank number befor WRAPLEN */
    int iblank = -1;
    /*  temp array store the WRAPLEN  */
    char temp[WRAPLEN];
    /*  the return char string after wrap line */
    char last[MAXCOL];

    for (i = 0; in[i] != '\0'; i++) {
        ;
        }
    inlen = i;
    i = 0;
    if (inlen <= WRAPLEN) {
        while ((out[iout++] = in[i++]) != '\0') {
            ;
            }
        out[iout] = '\0';
        last[0] = '\0';
        }
    else {
        for (i = 0; in[i] != '\0'; i++) {
            if (i < WRAPLEN) {
                temp[j++] = in[i];
                if ((in[i] == ' ') || (in[i] == '\t')) {
                    iblank = i;
                    }
                }
            else if (i == WRAPLEN) {
                if (iblank < 0) {
                    for (j = 0; j< WRAPLEN; j++) {
                        out[iout++] = temp[j];
                        }
                    out[iout++] = '\n';
                    last[ilast++] = in[i];
                    }
                else {
                    for (j = 0; j < WRAPLEN; j++) {
                        if (j <= iblank) {
                            out[iout++] = temp[j];
                            }
                        else {
                            last[ilast++] = temp[j];
                            }
                        }
                    out[iout++] = '\n';
                    last[ilast++] = in[i];
                    }
                }
            else {
                last[ilast++] = in[i];
                }
            }
        last[ilast] = '\0';
        //wrapline(out, iout, last);
        }
    if (ilast <= WRAPLEN) {

        for(i = 0; (out[iout++] = last[i]) != '\0'; i++) {
            ;
            }
        out[iout] = '\0';
        }
    else {
        wrapline(out, iout, last);
        }
    }
