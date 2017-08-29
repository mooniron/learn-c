/**************************************************************
* Name     :  ex7-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
exercise 7-3:
    revise minprintf to handle more of the other facilities of printf.
*/


/*
example: variable=length argument lists
    // ... : end of variant argument
    int printf(char *format, ...);
    //standard output, return the characters count
    int printf(char *format, arg1, arg2, ...);
    //store in string, return the characters count
    int sprintf(char *string, char *format, arg1, arg2, ...);

stdarg.h: macro definitions
    1.  va_list: to declare a variable that will refer to each argument in turn (i.e., ap);
    2.  va_start: initialize ap to point to the first unnamed argument;
        it must be called before use;
        the final named argument is used by va_start to get started.
    3.  va_arg: return one argument and step ap to the next;
        va_arg uses a type name to determine what type to return and how big a step to take.
    4.  va_end: does whatever cleanup is necessary;
        it must be called before the program returns.
*/


#include <stdarg.h>
#include <stdio.h>
// for isdigit
#include <ctype.h>

int minprintf(char *, ...);

/*  main: test block  */
int main(void) {
    int ival;
    double dval;
    char string[] = "I love you.\n";

    ival = -3;
    dval = 398708.14;

    minprintf("int = %5d, double = %e, %f, %g , string = %s\n", ival, dval, dval, dval, string);

    return 0;
    }   //end function main


/*  minprintf: minimal printf with variable argument list  */
int minprintf(char *fmt, ...) {
    /*  points to each unnamed arg in turn  */
    va_list ap;
    char *p, *sval, format[12];
    int ival, iform;
    int arguflag, leftflag, precisionflag;
    double dval;
    unsigned uval;

    //iform: index of format; arguflag: in or out arguflag; leftflag: left allign flag;
    iform = ival = 0;
    arguflag = leftflag = precisionflag = 0;
    dval = 0.0;

    /*  make ap point to 1st unnamed arg  */
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {
        //not in argument field
        if (arguflag == 0) {
            if (*p != '%') {
                putchar(*p);
                }
            else {
                //in argument field
                arguflag = 1;
                format[iform++] = *p;
                }
            continue;
            }   //end if

        // arguflag == 1; in argument field
        if (*p == '-') {
            if (leftflag == 0) {
                //set left allign flag 1, 0 for right allign
                leftflag = 1;
                format[iform++] = *p;
                continue;
                }
            else {
                printf("error: '-'\n");
                return -1;
                }
            }
        // a digit: width block and precision block
        if (isdigit(*p)) {
            format[iform++] = *p;
            continue;
            }
        // '.' block
        if (*p == '.') {
            if (precisionflag == 0) {
                precisionflag = 1;
                format[iform++] = *p;
                continue;
                }
            else {
                printf("error: '.'\n");
                return -1;
                }
            }   // periode block

        // format block
        switch (*p) {
            case 'd': case 'i': case 'c':
                format[iform++] = *p;
                format[iform] = '\0';
                ival = va_arg(ap, int);
                printf(format, ival);
                break;
            case 'u': case 'o': case 'x':
                format[iform++] = *p;
                format[iform] = '\0';
                uval = va_arg(ap, unsigned int);
                printf(format, uval);
                break;
            case 'f': case 'e': case 'g':
                format[iform++] = *p;
                format[iform] = '\0';
                dval = va_arg(ap, double);
                printf(format, dval);
                break;
            case 's':
                format[iform++] = *p;
                format[iform] = '\0';
                sval = va_arg(ap, char *);
                printf(format, sval);
                break;
            default:
                putchar(*p);
                break;
            }   //end switch

        //initialize flags and format index
        iform = 0;
        arguflag = leftflag = precisionflag = 0;
        }   //end for
    /*  clean up when done  */
    va_end(ap);

    return 0;
    }   //end function minprintf
