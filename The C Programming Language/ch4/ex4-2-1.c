/**************************************************************
* Name     :  ex4-2-1.c
* Author   :  Bronze Lee
* Version  :  0.1 scientific notation
* Date     :  2017年2月25日
**************************************************************/

#include <stdio.h>
#include <ctype.h>

#define MAXCOL 100

/*  rudimentary calculator  */
int main () {
    double sum, atof(char []);
    char line[MAXCOL];
    int getline(char line[], int max);

    sum = 0.0;
    while (getline(line, MAXCOL) > 0) {
        /*  %g width 6 and strip zero of the end  */
        printf ("\t%g\n", sum += atof(line));
        }
    return 0;
    }

/*  atof: couvert string s to double  */
double atof(char s[]) {
    double val, power, epower = 1;
    int i, sign, esign = 1;
    /*  skip white space  */
    for (i = 0; isspace(s[i]); i++) {
        ;
        }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
        }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        }
    if (s[i] == '.') {
        i++;
        }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
        }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        esign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-'  || s[i] == '+') {
            i++;
            }
        for (epower = 1.0; isdigit(s[i]) && (s[i] - '0'); s[i]--) {
            epower *= 10.0;
            }
        if (esign == -1) {
            return (sign * val / power) /epower;
            }
        else {
            return (sign * val / power) * epower;
            }
        }
    /*  return double value and the function is over
        if s have no digits, return defult 0  */
    return sign * val / power;
    }

/*  atoi: convert string s to integer using atof  */
int atoi(char s[]) {
    double atof(char s[]);

    return (int) atof(s);
    }

/*  getline: getline into s, return length  */
int getline(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
        }
    if (c == '\n') {
        s[i++] = c;
        }
    s[i] = '\0';
    return i;
    }
