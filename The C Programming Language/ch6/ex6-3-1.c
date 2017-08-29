/**************************************************************
* Name     :  ex6-3-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月21日
**************************************************************/


/*
exercise  6-3:
write a cross-referencer that prints a list of all words prints a list of all words in a
document, and for each word, a list of the line numbers on which it occurs.
Remove noise words like "the," "and," and so on.

best solution:
    write two data structures, wordtree and linetree
    wordtree: node contain a word and a list of line numbers it occurs, left and right subnodes.
    linetree: node contain a line number and a list of words that line, one subnode.

outline:
    1.  noise word can get from command line, set default noise words.
    2.  struct a word tree
        struct tword {
            //pointer to the text
            char *word;
            //number of line and occurrences
            struct tline *linenum;
            //left child
            struct tword *left;
            //right child
            struct tword *right;
        };
    3.  struct a line number tree
        struct tline {
            //current line number;
            int linen;
            //the word occurrences in line
            int count;
            struct tline *last;
            };

*/


/*
example: self-referential structures
count occurrences of all the input words.

// the tree node
struct tword {
    //points to the text
    char *word;
    //number of occurrences
    int count;
    //left child
    struct tword *left;
    //right child
    struct tword *right;
    };

It's illegal for a structure to contain an instance of itself, but
    struct tword *left;
declares left to be a pointer to a tword, not a tword itself.

*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

//stack struct line number
struct tline {
    //current line number;
    int linen;
    //the word occurrences in line
    int count;
    struct tline *last;
    };

//the tree word
struct tword {
    //pointer to the text
    char *word;
    //number of line and occurrences
    struct tline *linenum;
    //left child
    struct tword *left;
    //right child
    struct tword *right;
    };

//exercise 6-3
//struct tline *addlinen(struct tline *, int);
struct tword *addtree(struct tword *, char *, int);
void treeprint(struct tword *);
int getword(char *, int);
/*  return 0 if is not noise word, return 1 if is  */
int noiseword(char *, char **, int);
void qsort(char **, int, int);
//void shellsort(char **, int);

/*  word frequency count  */
int main(int argc, char *argv[]) {
    struct tword *root;
    //line number
    int linen = 1;
    char word[MAXWORD];

    root = NULL;

    /*  no argument  */
    if (argc == 1) {
        argv = NULL;
        //argv = {"the", "and"};
        }
    else {
        //skip the first item
        argc--;   //first index 0
        ++argv;
        //sort argv for binary search
        qsort(argv, 0, argc-1);
        //shellsort(argv, argc);
        /*while(argc--) {
            printf("%s ", *argv++);
            }
        printf("\n");  */
        }


    /*  addtree  */
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !noiseword(word, argv, argc)) {
            root = addtree(root, word, linen);
            }   //end if
        /*  a new line '\n'  */
        else if (word[0] == '\n') {
            linen++;
            }
        }   //end while

    treeprint(root);
    return 0;
    }   //end function main


/*  addtree block  */
//exercise 6-3 add
struct tline *addlinen(struct tline *, int);
struct tword *talloc(void);
char *strdup(char *);

/*  addtree: add a node with w, at or below p  */
struct tword *addtree(struct tword *p, char *w, int linen) {
    int cond;
    //exercise 6-3: the line node on the top of the stack
    //struct tline *lastline;

    /*  a new word has arrived  */
    if (p == NULL) {
        /*  make a new node  */
        p = talloc();
        p->word = strdup(w);
        //p->count = 1;
        p->left = p->right = NULL;
        //exercise 6-3 add
        //p->linenum = NULL;
        p->linenum = addlinen(NULL, linen);
        }
    /*  repeated word  */
    else if ((cond = strcmp(w, p->word)) == 0) {
        //p->count++;
        //exercise 6-3 add
        p->linenum = addlinen(p->linenum, linen);
        }
    /*  less than into left subtree  */
    else if (cond < 0) {
        p->left = addtree(p->left, w, linen);
        }
    /*  greater than into right subtree  */
    else {
        p->right = addtree(p->right, w, linen);
        }   //end if

    return p;
    }   //end function addtree

/*  addlinet: */
struct tline *addlinen(struct tline *linep, int n) {
    struct tline *next;

    //a new word, add root line number node
    if (linep == NULL) {
        //make a new node
        next = (struct tline *) malloc(sizeof(struct tline));
        next->last = linep;
        next->linen = n;
        next->count = 1;
        //return next;
        }
    else {
        //same line number
        if (n == linep->linen) {
            linep->count++;
            next = linep;
            }
        //a new line number > linen
        else {
            //make a new stack node
            next = (struct tline *) malloc(sizeof(struct tline));
            next->last = linep;
            next->linen = n;
            next->count = 1;
            //return next;
            }
        }   // end if (linep == NULL)
    return next;
    }   //end function addlinen


/*  treeprint block  */
void tlineprint(struct tline *);

/*  treeprint in-order print of tree p  */
void treeprint(struct tword *p) {
    if (p != NULL) {
        //print smaller tword tree than p
        treeprint(p->left);
        //print current tword
        //printf("%4d %s\n", p->count, p->word);
        printf("%18s\t", p->word);
        tlineprint(p->linenum);
        printf("\n");
        //print greater tword tree than p
        treeprint(p->right);
        }   //end if
    }   //end function print

/*  tlineprint: */
void tlineprint(struct tline *linep) {
    if (linep != NULL) {
        tlineprint(linep->last);
        printf("(ln: %d, cn: %d)\t", linep->linen, linep->count);
        }   //end if
    }   //end function tlineprint


/*  talloc block  */

//*  talloc: make a tword  *
struct tword *talloc(void) {
    return (struct tword *) malloc(sizeof(struct tword));
    }   //end function talloc


/*  make a duplicate of s  */
char *strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    /*  malloc returns NULL if no space is available  */
    if (p != NULL) {
        strcpy(p, s);
        }   //end if

    return p;
    }   //end function strdup


/*  getword: get next word or character from input  */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    //exercise 6-3: isspace include '\n'
    /*  skip spaces  */
    while (isspace(c = getch()) && c != '\n') {
        ;
        }   //end while

    if (c != EOF) {
        *w++ = c;
        }   //end if
    /*  isalpha: identify letters  */
    if (!isalpha(c)) {
        *w = '\0';
        return c;
        }   //end if
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


/*  noiseword: n is the length of char *noise[]  */
int noiseword(char *word, char **noise, int n) {
    int cond;
    char **low, **high, **mid;

    if (noise == NULL) {
        return 0;
        }

    low = noise;
    high = noise + n;

    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, *mid)) == 0) {
            return 1;
            }
        else if (cond > 0) {
            low = mid + 1;
            }
        else {
            //wrong: high = mid - 1; noise[-1] is illegal
            high = mid;
            }   //end if
        }   //end while
    //not found
    return 0;
    }   //end function noiseword


/*  qsort: quick sort v[left]...v[right]  */
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    //less than 2 items in array v
    if (left >= right) {
        return ;
        }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
            }   //end if
        }   //end for

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
    }   //end function qsort


/*  shellsort: n is length of the array v  */
void shellsort(char *v[], int n) {
    int i, j, gap;
    void swap(char *[], int, int);

    i = j = gap = 0;
    for (gap = n / 2; gap != 0; gap /= 2) {
        //
        for (i = 0; i < n - gap; i++) {
            //printf("i = %d %d\n", strcmp(v[i+gap], v[i]), i);
            for (j = i; j >= 0 && (strcmp(v[j + gap], v[j]) < 0); j -= gap) {
                swap(v, j, j + gap);
                //printf("j = %d, v[j] = %s\n", j, v[j]);
                }
            }
        }   //end for


    }   //end function shellsort


/*  swap: swap v[i], v[j]  */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    }   //end function swap
