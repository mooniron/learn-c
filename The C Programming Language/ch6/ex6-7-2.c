/**************************************************************
* Name     :  ex6-7-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: typedef
two main reasons for using typedefs:
    1.  to parameterize a program against portability problems, machine-dependent.
    2.  to provide better documentation for a program - may be easier to understand.
*/


/*  Length a synonym for int  */
typedef int Length;
Length max, min;
Length len[MAXLEN];

/*  String a synonym for char *  */
typedef char *String;
String p, lineptr[MAXLINES], alloc(int);
int strcmp(String, String);
p = (String) malloc(199);

/*  typedef for the tree nodes  */
typedef struct tnode *Treeptr;
/*  the tree node:  */
typedef struct tnode {
    //points to the text
    char *word;
    //number of occurrences
    int count;
    //left child
    struct tnode *left;
    //right child
    struct tnode *right;
    } Treenode;

Treeptr talloc(void) {
    return (Treeptr) malloc(sizeof(Treenode));
    }   //end function talloc


/*  typedef a pointer to function (of two char * arguments) return int  */
typedef int (*PFI) (char *, char *);
PFI strcmp, numcmp;

