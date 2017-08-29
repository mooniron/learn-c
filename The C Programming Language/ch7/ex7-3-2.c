/**************************************************************
* Name     :  ex7-3-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


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

void minprintf(char *, ...);

/*  main: test block  */
int main(void) {
    int ival;
    double dval;
    char string[] = "I love you.\n";

    ival = -3;
    dval = 3.14;

    printf("int = %d, double = %f, string = %s\n", ival, dval, string);

    return 0;
    }   //end function main


/*  minprintf: minimal printf with variable argument list  */
void minprintf(char *fmt, ...) {
    /*  points to each unnamed arg in turn  */
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    /*  make ap point to 1st unnamed arg  */
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
            }   //end if
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval != '\0'; sval++) {
                    putchar(*sval);
                    }   //end for sval
                break;
            default:
                putchar(*p);
                break;
            }   //end switch
        }   //end for
    /*  clean up when done  */
    va_end(ap);
    }   //end function minprintf
