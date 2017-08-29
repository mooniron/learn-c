/**************************************************************
* Name     :  ex1-21.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月21日
**************************************************************/

/*  function: convert input spaces to tabs and spaces. make smallest length  */

#include <stdio.h>
/* the max col of output*/
#define MAXCOL 1000
/* the max line of output */
#define MAXLINE 1000
/* define the number of spaces one tab */
#define TABSPACE 4
/* the state of in/out space */
#define IN 1
#define OUT 0


int getline(char line[], int maxcol);
int entabline(char out[], char in[]);

int main(void) {
    int i = 0;
    /*  the total number of lines  */
    int count;
    /*  the number of convert tabs  */
    int tabcount = 0;
    char line[MAXCOL];
    char output[MAXLINE][MAXCOL];

    while (getline(line, MAXCOL) > 0) {
        if (i <= MAXLINE) {
            tabcount += entabline(output[i++], line);
            }
        else {
            i++;
            }
        }
    /*  the total number of lines in output  */
    count = i;
    /* there was a line */
    if (count > 0) {
        printf("\n\nentap the input each %d spaces to one tab.\n\n", TABSPACE);
        printf("the total number of tabs is %d.\n", tabcount);
        printf("the total number of lines is %d.\n", count);
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

/*  detabline : convert the tabs of a line or string to certain spaces,
    return the total number of decode tabs  */
int detabline(char to[], char from[]) {
    int i, j;
    /*  the index of to  */
    int ito = 0;
    int tabnum = 0;
    /*  the tab state, out tab : tabstate = 0, in tab : tabstate = 1*/
    //int tabstate = 0;
    for (i = 0; from[i] != '\0'; i++) {
        if (from[i] == '\t') {
            tabnum++;
            for (j = 0; j < TABSPACE; j++) {
                to[ito++] = ' ';
                }
            }
        else {
            to[ito++] = from[i];
            }
        }
    /*  the end flag '\0'  */
    to[ito] = '\0';
    /*  return the total number of detabed tabs  */
    return tabnum;
    }

/*  entabline : convert the spaces of a line or string to tabs and certain spaces,
    each 4 spaces is one tab. return the total number of decode tabs  */
int entabline(char out[], char in[]) {
    int i, j;
    /*  the index of out  */
    int ito = 0;
    /*  the number of space between nonspace  */
    int spacenum = 0;
    /*  the number of converted tab  */
    int tabnum = 0;
    /*  the space state, out space : tabstate = 0, in space : tabstate = 1*/
    int spacestate = OUT;
    for (i = 0; in[i] != '\0'; i++) {
        if (in[i] == ' ') {
            /*  last char is not space, the first space, start count the spaces*/
            if (spacestate == OUT) {
                spacenum = 1;
                spacestate = IN;
                }
            spacenum++;
            }
        else {
            if (spacestate == OUT) {
                out[ito++] = in[i];
                }
            else {
                /*  each 4 spaces to one tab  */
                for (j = 0; j < (spacenum / TABSPACE); j++) {
                    out[ito++] = '\t';
                    tabnum++;
                    }
                /*  store the spaces < 4 to out */
                for (j = 0; j < (spacenum % TABSPACE); j++) {
                    out[ito++] = ' ';
                    }
                spacestate = OUT;
                }
            }
        }
    /*  the end flag '\0'  */
    out[ito] = '\0';
    /*  return the total number of detabed tabs  */
    return tabnum;
    }
