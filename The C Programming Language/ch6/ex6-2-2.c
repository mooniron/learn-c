/**************************************************************
* Name     :  ex6-2-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月21日
**************************************************************/


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

#define MAXWORD 100

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

    treeprint(root);
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
