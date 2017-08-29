/**************************************************************
* Name     :  ex6-4-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月21日
**************************************************************/


/*
version 0.1: array version
*/


/*
exercise 6-4:
write a program that prints the distinct words in its input sorted into decreasing order of
frequency of occurrence. precede each word by its count.

outline:
    1. count input words, add words to tree
    2. after input stop, store words tree in a array
    3. quick sort the array
    4. print the array
*/


/*
example: self-referential structures
count occurrences of all the input words.

// the tree node
struct tnode {
    //points to the text
    char *word;
    //number of occurrences
    int count;
    //left child
    struct tnode *left;
    //right child
    struct tnode *right;
    };

It's illegal for a structure to contain an instance of itself, but
    struct tnode *left;
declares left to be a pointer to a tnode, not a tnode itself.

*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXWORDS 10000

//exercise 6-4
struct wordc {
    char *word;
    int count;
    };

//exercise 6-4
//array of words
struct wordc wordfreq[MAXWORDS];
//total number of words in the tree
int wordsnum = 0;

//the tree node
struct tnode {
    //pointer to the text
    char *word;
    //number of occurrences
    int count;
    //left child
    struct tnode *left;
    //right child
    struct tnode *right;
    };

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
//exercise 6-4
void treetoarray(struct tnode *);
void freqqsort(struct wordc *, int, int);
void freqprint(struct wordc *, int);

/*  word frequency count  */
int main(void) {
    struct tnode *root;

    char word[MAXWORD];

    root = NULL;
    /*  addtree  */
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
            }   //end if
        }   //end while

    //treeprint(root);
    //exercise 6-4
    //wordfreq = (struct wordc *) malloc(sizeof(struct wordc));
    treetoarray(root);
    freqqsort(wordfreq, 0, wordsnum-1);
    freqprint(wordfreq, wordsnum);

    return 0;
    }   //end function main


/*  addtree block  */
struct tnode *talloc(void);
char *strdup(char *);

/*  addtree: add a node with w, at or below p  */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    /*  a new word has arrived  */
    if (p == NULL) {
        /*  make a new node  */
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        }
    /*  repeated word  */
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        }
    /*  less than into left subtree  */
    else if (cond < 0) {
        p->left = addtree(p->left, w);
        }
    /*  greater than into right subtree  */
    else {
        p->right = addtree(p->right, w);
        }   //end if

    return p;
    }   //end function addtree


/*  treeprint in-order print of tree p  */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        //print smaller tnode tree than p
        treeprint(p->left);
        //print current tnode
        printf("%4d %s\n", p->count, p->word);
        //print greater tnode tree than p
        treeprint(p->right);
        }   //end if
    }   //end function print


/*  talloc block  */
#include <stdlib.h>

//*  talloc: make a tnode  *
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
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

    /*  skip spaces  */
    while (isspace(c = getch())) {
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


//exercise 6-4

/*  tree to array block  */
//
void treetoarray(struct tnode *p) {
    if (p != NULL) {
        treetoarray(p->left);
        //current node
        //wordfreq = (struct wordc *) malloc(sizeof(struct wordc));
        wordfreq[wordsnum].word = p->word;
        wordfreq[wordsnum].count = p->count;
        wordsnum++;
        //wordfreq++;
        //
        treetoarray(p->right);
        }
    }   //end function treetoarray


/*  freqqsort:  */
void freqqsort(struct wordc *wordcp, int left, int right) {
    int last, i;
    void swap(struct wordc *, int, int);

    if (left >= right) {
        return;
        }

    swap(wordcp, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (wordcp[i].count > wordcp[left].count) {
            swap(wordcp, ++last, i);
            }
        else if (wordcp[i].count == wordcp[left].count) {
            //if count equal, sort alphatically
            if (strcmp(wordcp[i].word, wordcp[left].word) < 0) {
                swap(wordcp, ++last, i);
                }
            }
        }   //end for

    swap(wordcp, left, last);
    freqqsort(wordcp, left, last-1);
    freqqsort(wordcp, last+1, right);
    }   //end function freqqsort

/*  swap  */
void swap(struct wordc *p, int i, int j) {
    struct wordc temp;

    //temp.word = p[i].word;
    //temp.count = p[i].count;
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
    }   //end function swap


//exercise 6-4
/*  freqprint block  */
void freqprint(struct wordc *p, int n) {
    while(n--) {
        printf("%12s %4d\n", p->word, p->count);
        p++;
        }
    }   //end function freqprint
