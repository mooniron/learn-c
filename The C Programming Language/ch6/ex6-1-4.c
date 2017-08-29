/**************************************************************
* Name     :  ex6-1-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月16日
**************************************************************/


/*
example: pointers to structures
keyword-counting program: pointer version
    modify main and binsearch block
*/

/*
because of alignment requirements for different objects, there may be
unnamed "holes" in a structure.
Thus, for instance, if a char is 1 byte and an int is 4 bytes, the structure
    struct {
        char c;
        int i;
        }
might well require eight bytes, not five.
*/


/*
exercise 6-1:
modify getword:
    properly handle underscores, string constants, comments, or preprocessor control lines.
outline:
    extend struct key to comment count, quote count
*/


/*
example: arrays of structures
count C keywords:
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>


#define MAXWORD 100


struct key {const char *word; int count; int quoten; int commentn;} keytab[] = {
    {"#define", 0, 0, 0},
    {"#else", 0, 0, 0},
    {"#if", 0, 0, 0},
    {"#include", 0, 0, 0},
    {"auto", 0, 0, 0},
    {"break", 0, 0, 0},
    {"case", 0, 0, 0},
    {"char", 0, 0, 0},
    {"const", 0, 0, 0},
    {"continue", 0, 0, 0},
    {"default", 0, 0, 0},
    {"else", 0, 0, 0},
    {"float", 0, 0, 0},
    {"for", 0, 0, 0},
    {"if", 0, 0, 0},
    {"int", 0, 0, 0},
    /* ... */
    {"unsigned", 0, 0, 0},
    {"void", 0, 0, 0},
    {"volatile", 0, 0, 0},
    {"while", 0, 0, 0},
    };

//#define NKEYS (sizeof keytab / sizeof(struct key))
#define NKEYS (int) (sizeof keytab / sizeof(keytab[0]))

/*  double quoto  */
int inquote = 0;
/*  multi-comment  */
int incomment = 0;
/*  quote-comment  */
int inquotecom = 0;
/*  comment-quote  */
int incomquote = 0;
/*  quote temp count  */
int quotetemp[NKEYS];
/*  comment temp count  */
int comtemp[NKEYS];
/*  token getword  */
enum token {TOK_COMBEGIN = UCHAR_MAX + 1, TOK_COMEND};

int getword(char *, int);
/*  return a pointer to struct key type  */
struct key *binsearch(char *, struct key *, int);
void addstructarray(struct key *, int *, int, int);
void adddigitarray(int *, int *, int);
void cleartemp(int *, int);


/*  count C keywords; pointer version  */
int main(void) {
    int n;
    char word[MAXWORD];
    struct key *p;

    n = 0;
    /*  initial temp array  */
    cleartemp(quotetemp, NKEYS);
    cleartemp(comtemp, NKEYS);

    /*  count block  */
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || (word[0] == '#' && isalpha(word[1]))) {
            if ((p = binsearch(word, keytab, NKEYS)) != NULL) {
                if (inquote > 0 || incomquote > 0) {
                    quotetemp[n]++;
                    }   //end if
                else if (incomment > 0 || inquotecom > 0) {
                    comtemp[n]++;
                    }   //end if
                else {
                    p->count++;
                    }   //end if
                }   //end if binsearch
            }   //end if
        }   //end while

/*    printf("inquote = %d, inquotecom = %d, incomment = %d, incomquote = %d\n", \
        inquote, inquotecom, incomment, incomquote);  */
    /*  add temp block  */
    if (inquote > 0) {
        addstructarray(keytab, quotetemp, NKEYS, 2);
        addstructarray(keytab, comtemp, NKEYS, 3);
        }
    else if (incomment > 0) {
        addstructarray(keytab, comtemp, NKEYS, 1);
        addstructarray(keytab, quotetemp, NKEYS, 2);
        }
    else if (inquotecom > 0 || incomquote > 0) {
        addstructarray(keytab, comtemp, NKEYS, 1);
        addstructarray(keytab, quotetemp, NKEYS, 1);
        }

    /*  print block  */
    for (p = keytab; p < keytab + NKEYS; p++) {
        if (p->count > 0) {
            printf("p->count = %4d %s\n", p->count, p->word);
            }   //end if
        if (p->quoten > 0) {
            printf("p->quoten = %4d %s\n", p->quoten, p->word);
            }
        if (p->commentn > 0) {
            printf("p->commentn = %4d %s\n", p->commentn, p->word);
            }
        }   //end for

    return 0;
    }   //end function main


/*  example pointer version  */
/*  binsearch: find word in tab[0]...tab[n-1] in increasing order  */
struct key *binsearch(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    /*  illegal to dereference the &tab[n]  */
    struct key *high = &tab[n];
    struct key *mid;


    while (low < high) {
        /*  the addition of pointers is illegal  */
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0) {
            high = mid;
            }
        else if (cond > 0) {
            low = mid + 1;
            }
        else {
            return mid;
            }   //end if
        }   //end while

    /*  not found  */
    return NULL;
    }   //end function binsearch


/*  getword: get next word or character from input  */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    /*  skip spaces  */
    while (isspace(c = getch())) {
        ;
        }   //end while

    if (c != EOF) {
        *w++ = c;
        }   //end if
    /*  isalpha: identify letters  */
    if (!isalpha(c) && c != '"' && c != '/' && c != '*' && c != '#') {
        *w = '\0';
        return c;
        }   //end if


    /*  quote string block  */
    if (c == '"') {
        /*  when incomment > 0, all other flag == 0  */
        if (incomment > 0) {
            incomment = 0;
            incomquote++;
            /*  add to quote temp  */
            }
        //
        else if (incomquote > 0) {
            incomquote = 0;
            incomment++;
            /*  add to quote temp  */
            }
        //
        else if (inquote > 0) {
            inquote = 0;
            /*  add quote temp to quote  */
            /*  add comment temp and quote temp to quote  */
            adddigitarray(quotetemp, comtemp, NKEYS);
            addstructarray(keytab, quotetemp, NKEYS, 2);
            /*  clear comment temp and quote temp  */
            cleartemp(comtemp, NKEYS);
            cleartemp(quotetemp, NKEYS);
            }
        /*  when inquotecom > 0, inquote = 0, incomment = 0, incomquote = 0  */
        else if (inquotecom > 0) {
            inquotecom = 0;
            /*  add comment temp and quote temp to quote  */
            adddigitarray(quotetemp, comtemp, NKEYS);
            addstructarray(keytab, quotetemp, NKEYS, 2);
            /*  clear comment temp and quote temp  */
            cleartemp(comtemp, NKEYS);
            cleartemp(quotetemp, NKEYS);
            }
        /*  all four flag are zero  */
        else {
            inquote++;
            /*  add to quote temp  */
            }   //end if

        *w = '\0';
        return c;
        }   //end if

    /*  comment begin block  */
    if (c == '/') {
        if ((c = getch()) != '*') {
            ungetch(c);
            *w = '\0';
            return word[0];
            }
        else {
            /*  when inquote > 0, inquotecom == 0, incomment == 0, incomquote == 0  */
            if (inquote > 0) {
                inquote = 0;
                inquotecom++;
                /*  add to comment temp  */
                }
            else if (incomment == 0 && incomquote == 0) {
                incomment++;
                /*  add to comment temp  */
                }

            *w++ = c;
            *w = '\0';
            return TOK_COMBEGIN;
            }   //end if
        }   //end if comment begin block

    /*  comment end block  */
    if (c == '*') {
        /*  not the comment end  */
        if ((c = getch()) != '/') {
            ungetch(c);
            *w = '\0';
            return word[0];
            }
        /*  comment end token  */
        else {
            /*  */
            if (incomment > 0) {
                incomment = 0;
                /*  add comment temp and quote temp to comment  */
                adddigitarray(comtemp, quotetemp, NKEYS);
                addstructarray(keytab, comtemp, NKEYS, 3);
                /*  clear comment and quote temp  */
                cleartemp(quotetemp, NKEYS);
                cleartemp(comtemp, NKEYS);
                }
            else if (incomquote > 0) {
                incomquote = 0;
                /*  add comment and quote temp to comment  */
                adddigitarray(comtemp, quotetemp, NKEYS);
                addstructarray(keytab, comtemp, NKEYS, 3);
                /*  clear comment and quote temp  */
                cleartemp(quotetemp, NKEYS);
                cleartemp(comtemp, NKEYS);
                }
            else if (inquotecom > 0) {
                inquotecom = 0;
                inquote++;
                /*  add to quote temp  */
                }   //end if

            *w++ = c;
            *w = '\0';
            return TOK_COMEND;
            }   //end if
        }   //end if comment end block

    /*  # block  */
    if (c == '#') {
        if (!isalpha(c = getch())) {
            ungetch(c);
            *w = '\0';
            return word[0];
            }
        else {
            *w++ = c;
            }
        }   //end if # block

    /*  isalnum: identify letters and digits  */
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
            }
        }   //end for
    *w = '\0';

    return word[0];
    }   //end function getword


/*  getch block  */
int ch;
int ungetflag = 0;

int getch(void) {
    if (ungetflag == 1) {
        ungetflag = 0;
        return ch;
        }
    else {
        return getchar();
        }
    }   //end function getch

void ungetch(int c) {
    if (ungetflag == 0) {
        ch = c;
        ungetflag = 1;
        }
    else {
        printf("error: there is already a character in stack\n");
        }
    }   //end function ungetch


/*  adddstructarray  */
void addstructarray(struct key *s, int *t, int n, int c) {

    while(n-- > 0) {
        switch(c) {
            case 1:
                s->count += *t;
                break;
            case 2:
                s->quoten += *t;
                break;
            case 3:
                s->commentn += *t;
                break;
            default:
                break;
            }   //end switch
        s++;
        t++;
        }   //end while
    }   //end function addstructarray


/*  add two digital array  */
void adddigitarray(int *s, int *t, int n) {
    while(n-- > 0) {
        *s += *t;
        s++;
        t++;
        }   //end while
    }   //end function adddigitarray

/*  cleartemp: set each element in temp array to 0  */
void cleartemp(int *s, int n) {
    while(n-- > 0) {
        *s++ = 0;
        }   //end while
    }   //end function cleartemp
