/**************************************************************
* Name     :  ex2-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年2月23日
**************************************************************/

/*  function : convert a string of hexadecimal digit s to its numeric value
    */
#include <stdio.h>

/*  htoi: convert s to integer  */
int htoi(char s[]) {
    int i, n;
    i = n = 0;
    while (s[i++] != '\0') {
        ;
        }

    if (i >= 3 && (s[0] == '0' && (s[1] == 'X' || s[1] == 'x'))) {
        i = 2;
        while (s[i] != '\0') {
            if (s[i] >= '0' && s[i] <= '9' ) {
                n = n * 16 + (s[i] - '0');
                }
            else if (s[i] >= 'A' && s[i] <= 'F') {
                n = n * 16 + (s[i] - 'A' + 10);
                }
            else if (s[i] >= 'a' && s[i] <= 'f') {
                n = n * 16 + (s[i] - 'a' + 10);
                }
            else {
                printf ("ERROR: NOT A HEX DIGIT STRING.\n");
                n = 0;
                }
            i++;
            }
        }
    else {
        printf ("ERROR: NOT A HEX DIGIT STRING.\n");
        n = 0;
        }

    return n;
    }

int main() {
    int i = 0;
    int c;
    int result;
    char input[100];
    printf ("input a hex number :\n");
    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            input[i++] = c;
            }
        else {
            input[i] = '\0';
            result = htoi(input);
            printf ("0xa1 = %d .\n", result);
            i = 0;
            }
        }
    }
