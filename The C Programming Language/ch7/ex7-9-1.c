/**************************************************************
* Name     :  ex7-9-1.c
* Author   :  Bronze Lee
* Version  :  0.2
* Date     :  2017年3月29日
**************************************************************/


/*
exercise 7-9:
    functions like isupper can be implemented to save space or to save time.
    explore both possibilities.

    This question is best left to an essay rather than code, so here's my take: The easiest way
to implement the eleven is() functions in C90's version of <ctype.h> is via a table lookup. If
UCHAR_MAX is 255, then a table would take up around 514 8-bit bytes and still have room for five
more is() functions. In modern programs, this is a miniscule expense of both space and time
since a mere table lookup doesn't cost a whole lot (although space may be a priority for
embedded systems). Additionally, since the is() functions of <ctype.h> are locale-dependent and
therefore subject to locale-specific whims, a table could more easily be modified than
modifying hard calculations.

*/


/*
example: miscellaneous  functions; standard library

1.  string operations;
    char *s, *t; int n, c;
    strcat(s, t);
    strncat(s, t, n);
    strcmp(s, t);
    strncmp(s, t, n);
    strcpy(s, t);
    strncpy(s, t, n);
    strlen(s);
    strchr(s, c);
    strrchr(s, c);

2.  character class testing and conversion : ctype.h
    int c; return int;
    isalpha(c);
    isupper(c);
    islower(c);
    isdigit(c);
    isalnum(c);
    isspace(c);
    toupper(c);
    tolower(c);

3.  ungetc: int ungetc(int c, FILE *fp);
    it pushes the character c back onto file fp, and returns either c, or EOF for an error.
only one character of pushback is guaranteed per file.

4.  command execution;
    system(char *s) executes the command contained in the character string s, then resumes
execution of the current program.
    for UNIX, system("date") causes the program date to be run, return the status value
returned by exit.

5.  storage management: malloc, calloc
    malloc and calloc obtain blocks of memory dynamically.
    void *malloc(size_t n): malloc returns a pointer to n bytes of uninitialized storage,
or NULL if the request can not be satisfied.
    void *calloc(size_t n, size_t size): calloc returns a pointer to enough free space for
an array of n objects of the specified size, or NULL if the request cannot be satisfied.
the storage is initialized to zero.
    int *ip;
    ip = (int *) calloc(n, sizeof(int));
    free(p) frees the space pointed to by p, where p was originally obtained by a call to
malloc or calloc. it is a ghastly error to free something not obtained by calling malloc
or calloc. it is also an error to use something after it has been freed.

6. mathematical functions: math.h; double arguments and return a double.
    sin(x);
    cos(x);
    atan2(y, x);
    exp(x);
    log(x);
    log10(x);
    pow(x, y);
    sqrt(x);
    fabs(x);

7.  random number generation: rand();
    rand() computes a sequence of pseudo-random integers in the range zero to RAND_MAX.
    srand(unsigned) sets the seed for rand.
*/


/*  Consider the following three implementations of isupper() :  */

//Implementation #1:
int isupper(int c) {
    // fails in EBCDIC
    return (c >= 'A' && c <= 'Z');
    }   //end function isupper

//Implementation #2:
int isupper(int c) {
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
    }

//Implementation #3:
/* Presumably, _UP is a power of 2 and
 * _Ctype is a table
 */

int isupper(int c) {
    return ((_Ctype[(unsigned char)c] & _UP) != 0);
    }
