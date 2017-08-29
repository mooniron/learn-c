/**************************************************************
* Name     :  ex7-4-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
exercise 7-4:
    write a private version of scanf analogous to minscanf from the previous section
*/


/*
example: formatted standard output scanf
    //arg1 and arg2 ... are pointers responding to format argument;
    int scanf(char *format, arg1, arg2, ...);
    //read string instead of standard input
    int sscanf(char *string, char *format, ...);

1.  rudimentary calculator of chapter 4:
    written with scanf to do the input conversion;
warning:
    all arguments of scanf and sscanf are pointers.

rudimentary calculator:
read dates of form:
    12 Dec 2017
    mm/dd/yy;
*/


#include <stdarg.h>
#include <stdio.h>
// for isdigit
#include <ctype.h>

#define MAXLEN 1000

int minscanf(char *, ...);

/*  main: test block  */
int main(void) {
    int ival;
    float dval;
    char string[] = "i love program\n";

    ival = -3;
    dval = 398708.14;
    printf("ival = %d, dval = %g\n", ival, dval);
    minscanf("int = %5d, double = %f, string = %12s", &ival, &dval, string);
    printf("ival = %d, dval = %g, string = %s\n", ival, dval, string);

    return 0;
    }   //end function main


/*  minscanf: minimal printf with variable argument list  */
int minscanf(char *fmt, ...) {
    /*  points to each unnamed arg in turn  */
    va_list ap;
    char *p, *sptr, format[MAXLEN];
    int *iptr, iform;
    int arguflag;
    double *dptr;
    unsigned *uptr;

    //iform: index of format; arguflag: in or out arguflag;
    iform = 0;
    arguflag = 0;
    iptr = NULL;
    dptr = NULL;
    uptr = NULL;
    sptr = NULL;

    /*  make ap point to 1st unnamed arg  */
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {
        //not in argument field
        if (arguflag == 0) {
            format[iform++] = *p;
            if (*p == '%') {
                //in argument field
                arguflag = 1;
                //format[iform++] = *p;
                }
            continue;
            }   //end if

        // a digit: width block and precision block
        if (isdigit(*p)) {
            format[iform++] = *p;
            continue;
            }

        // format block
        switch (*p) {
            case 'd': case 'i': case 'c':
                format[iform++] = *p;
                format[iform] = '\0';
                iptr = va_arg(ap, int *);
                scanf(format, iptr);
                break;
            case 'u': case 'o': case 'x':
                format[iform++] = *p;
                format[iform] = '\0';
                uptr = va_arg(ap, unsigned int *);
                scanf(format, uptr);
                break;
            case 'f': case 'e': case 'g':
                format[iform++] = *p;
                format[iform] = '\0';
                dptr = va_arg(ap, double *);
                scanf(format, dptr);
                break;
            case 's':
                format[iform++] = *p;
                format[iform] = '\0';
                sptr = va_arg(ap, char *);
                scanf(format, sptr);
                break;
            default:
                format[iform++] = *p;
                break;
            }   //end switch

        //initialize flags and format index
        iform = 0;
        arguflag = 0;
        }   //end for
    /*  clean up when done  */
    va_end(ap);

    return 0;
    }   //end function minscanf

