/**************************************************************
* Name     :  ex2-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月23日
**************************************************************/

/*  function : strlen , the length of a string
    */
#include <stdio.h>
#define MAXCOL 1000

/*  strlen: return length of in  */
int strlen(char in[])
{
    int len;
    for (len = 0; in[len] != '\0'; len++) {
        ;
        }
    return len;
}

/*  leap year  */
void leapyear(int year) {

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf ("%d is a leap year.\n", year);
        }
    else {
        printf ("%d is not a leep year.\n", year);
        }
    }

int getline(char out[], int slim) {
    int i = 0;
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            break;
            }
        else if (i < slim -1) {
            out[i++] = c;
            }
        else {
            i++;
            }
        }
    out[i] = '\0';
    return i;
    }

int strlen(char in[]);
void leapyear(int year);
int getline(char out[], int slim);

int main() {

    int i;
    int len;
    int year[10];
    char line[MAXCOL];
    //  leap year
    year[0] = 1900;
    for (i = 0; i < 10; i++) {
        if (i > 0) {
            year[i] = year[i-1] + 20;
            }
        leapyear(year[i]);
        }
    //  get line and strlen
    len = getline(line, MAXCOL);
    if (len == strlen(line)) {
        printf ("that is right.\n");
        }
    else {
        printf ("there is some wrong.\n");
        }
    }
