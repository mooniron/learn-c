/**************************************************************
* Name     :  ex7-2-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
exercise 7-2:
    write a program that will print arbitrary input in a sensible way. as a minimum,
it should print non-graphic(not printable) characters in octal or hexadecimal according to local custom,
 and break long text lines.
*/

/*
example: format out printf
    //print most 'max' characters from a string s
    printf("%.*s", max, s);
    //'-': left allign; width: field width; h: short; l: long; all parameters are optional;
    printf("%(-)width.precision(d, i, o, x, f, e, g, s, p, %)(h, l)");
    //standard output, return the characters count
    int printf(char *format, arg1, arg2, ...);
    //store in string, return the characters count
    int sprintf(char *string, char *format, arg1, arg2, ...);
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int getlineext(char *, const char *, int);
int wrapline(char *, char *, int);

int main(int argc, char *argv[]) {
    int c, wraplen;
    char line[MAXLEN], outline[MAXLEN];
    //char format[9];
    const char *format;

    struct {
        int oct;
        int hex;
        } flags;

    flags.oct = flags.hex = 0;
    c = 0;

    //argv command line arguments process
    while(--argc && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch(c) {
                //oct
                case 'o':
                    flags.oct = 1;
                    flags.hex = 0;
                    break;
                //hex
                case 'x':
                    flags.hex = 1;
                    flags.oct = 0;
                    break;
                //number for wraplen
                case '0': case '1': case '2': case '3': case '4': case '5': \
                case '6': case '7': case '8': case '9':
                    wraplen = wraplen * 10 + (c - '0');
                    break;
                //other
                default:
                    printf("unknown command\n");
                    break;
                }   //end switch
            }   //end while c != '\0'
        }   //end while (--argc)

    //format block
    if (flags.oct > 0) {
        format = "0%3o";
        }
    else if (flags.hex > 0) {
        format = "0x%2x";
        }
    else {
        //default
        format = "0x%2x";
        }   //end if format

    //line process
    if (argc != 0) {
        printf("usage: exe -x80 / -o80 / -x -80 / -o -80\n");
        }
    else {
        while (getlineext(line, format, MAXLEN) > 0) {
            wrapline(outline, line, wraplen);
            printf("%s", outline);
            }
        }   //end if argc != 0

    return 0;
    }   //end function main


/*  canprint: return 1 if c is printable, else return 0  */
int canprint(int c)  {
    int found = 0;
    //const char *s;
    char *s;
    //const char *printable = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 !\"#%&'()*+,-./:;<=>?[\\]^_{|}~\t\f\v\r\n";
    char printable[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 !\"#%&'()*+,-./:;<=>?[\\]^_{|}~\t\f\v\r\n";

    for (s = printable; !found && *s != '\0'; s++) {
        if (*s == c) {
            found = 1;
            }
        }   //end for
    //not found
    return found;
    }   //end function canprint


int getlineext(char *s, const char *format, int lim) {
    int i, c, width;

    i = c = width = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        //printable
        if (canprint(c) > 0) {
            *s++ = c;
            }
        //can not print
        else {
            width = sprintf(s, format, c);
            //width is 6
            s += width;
            *s++ = ' ';
            i += width;
            }   //end if canprint
        }   //end for

    if (c == '\n') {
        *s++ = c;
        i++;
        }
    *s = '\0';

    return i;
    }   //end function getlineext


/*  wrapline : intelligent line wrap. convert in[] to out[].
    the max length of out line is "wraplen"  */
int wrapline(char *out, char *in, int wraplen) {

    int i, j;
    /*  the index of temp */
    int itemp = 0;
    /*  the index of out */
    int iout = 0;
    /*  the number of out lines  */
    int outline = 0;
    /*  the last blank number befor wraplen */
    int iblank = -1;
    /*  temp array store the wraplen  */
    char *temp;

    temp = (char *) malloc(wraplen);
    i = j = 0;
    for (i = 0; in[i] != '\0'; i++) {

        if (itemp < wraplen) {
            temp[itemp] = in[i];
            // store the index of  the last blank or tab.
            if ((temp[itemp] == ' ') || (temp[itemp] == '\t')) {
                iblank = itemp;
                }
            itemp++;
            }
        else {
            // itemp == wraplen, initialize itemp to 0.
            itemp = 0;
            // there is no blank in temp, current wraplen length input
            if (iblank < 0) {
                for (j = 0; j < wraplen; j++) {
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
                for (j = 0; j < wraplen; j++) {
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
    /*  temp[] : the string length < wraplen, store in temp[], before '\0',
        copy temp to out.  the last line so far  */
    for (j = 0; j < itemp; j++) {
        out[iout++] = temp[j];
        }
    outline++;
    // the end flag '\0'
    out[iout] = '\0';
    return outline;
    }   //end function wrapline


void strcomb(char begin[], char end[]) {
    int i,j;
    for (i = 0; begin[i] != '\0'; i++) {
        ;
        }
    for (j = 0; end[j] != '\0'; j++) {
        begin[i++] = end[j];
        }
    begin[i] = '\0';
    }   //end function strcomb
