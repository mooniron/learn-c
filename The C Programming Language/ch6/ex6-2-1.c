/**************************************************************
* Name     :  ex6-2-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月21日
**************************************************************/


/*
exercise 6-2:
    Write a program that reads a C program and prints in alphabetical order each group of
    variable names that are identical in the first 6 characters, but different somewhere
    thereafter. Don't count words within strings and comments.
    make 6 a parameter that can be set from the command line.
outline:
    1.  add a function headsame to identify a string is identical in the first 6 characters;
        return 1 if input words is, or 0 if not.
    2.  modify strcmph:
        int strcmphh(char *s, char *t);
        if s is headsame and t is not, s < t, return < 0;
        else if s is not headsame and t is , s > t, return > 0;
        else compare them normally.
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
/*  for atoi  */
#include <stdlib.h>

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

/*  the number of identical in the first characters  */
int headn = 0;

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/*  word frequency count; print same head character firstly  */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    /*  no argument  */
    if (argc == 1) {
        //default value
        headn = 6;
        }
    else if (argc == 2) {
        headn = atoi(argv[1]);
        }
    else {
        printf("usage: exe number\n");
        }   //end if

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


/*  exercise 6-2; add a strcmphh function  */
int strcmph(char *, char *);
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
    else if ((cond = strcmph(w, p->word)) == 0) {
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


/*  exercise 6-2  */
/*  strcmph block  */
/*  headsame: return 1 if first 6 characters are same, or 0 if not  */
int headsame(char *);

/*  strcmph: compare two words, headsame words are smallest  */
int strcmph(char *s, char *t) {

    if (headsame(s) > 0 && headsame(t) == 0) {
        return -1;
        }
    else if (headsame(s) == 0 && headsame(t) > 0) {
        return 1;
        }
    else {
        return strcmp(s, t);
        }   //end if

    }   //end function strcmph


/*  headsame: return 1 if first 6 characters are identical, or 0 if not  */
int headsame(char *s) {

    int n = headn;

    /*  request less than 1 character identical  */
    if (n <= 1) {
        return 1;
        }
    /*  length less than headn  */
    /*else if (strlen(s) < headn) {
        return 0;
        }*/
    else {
        /*  headn  */
        while (*s != '\0' && *(s+1) == *s && --n > 1) {
            s++;
            }
        }//end if

    if (n == 1) {
        return 1;
        }
    else {
        return 0;
        }

    }   //end function headsame
