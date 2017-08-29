/**************************************************************
* Name     :  ex6-6-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
exercise 6-6:
    implement a simple version of the #define processor (i.e., no arguments) suitable for
C programs, based on the routines of this section. you may also find getch and ungetch helpful.
*/


/*
exercise 6-5:
    write a function undef that will remove a name and definetion from the table
maintained by lookup and install.

outline:
    int undefine(char *name);
    there are three cases for the undefined name;
    1.  the head hashtab[hashval], return 1;
    2.  the middle item in the list, return 1;
    3.  not found, return 0;
*/


/*
pointer version:
*/


/*
example: table lookup, hash-search
symbol table management routines of a macro processor or a compiler.
    #define IN 1
function:
    hash, lookup, install;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//max line length
#define MAXLEN 1000
//max number of words each line
#define MAXWORDS 100
#define HASHSIZE 101

/*  table entry  */
struct nlist {
    /*  next entry in chain  */
    struct nlist *next;
    /*  defined name  */
    char *name;
    /*  replacement text  */
    char *defn;
    };

/*  pointer table  */
static struct nlist *hashtab[HASHSIZE];
const char *macrotoken[] = {
    "#define",
    "#undefine"
    };

int getline(char *, int);
int spacesplit(char **, char *, int, int);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undefine(char *);

/*  main block: test  */
int main(void) {
    int i = 0, j = 0, len;
    char line[MAXLEN], **words;
    struct nlist *np;

    words = (char **) malloc(sizeof(char *) * MAXWORDS);

    while ((len = getline(line, MAXLEN)) > 0) {
        i = spacesplit(words, line, len, MAXWORDS);

        //printf("***%s***\n", *words);

        //begin with #, macro
        if (line[0] == '#') {
            if (i == 3) {
                //#define
                if (strcmp(words[0], macrotoken[0]) == 0) {
                    if ((install(words[1], words[2])) == NULL) {
                        printf("no room for #define\n");
                        }
                    }   //end #define
                }
            else if (i == 2) {
                if (strcmp(words[0], macrotoken[1]) == 0) {
                    if (undefine(words[1]) == 0) {
                        printf("not found %s\n", words[1]);
                        }
                    else {
                        printf("undefine %s successfully\n", words[1]);
                        }
                    }
                }   //end else if   */
            else {
                printf("usage: #define MAXLEN 1000\n");
                printf("usage: #undefine MAXLEN\n");
                }   //end else
            }   //end if #
        else {
            for(j = 0; j < i; j++) {
                if ((np = lookup(words[j])) != NULL) {
                    printf("replace %s to %s successfully\n", np->name, np->defn);
                    }
                }
            }   //end else #
        }   //end while

    return 0;
    }   //end function


int getline(char *s, int lim) {
    int i = 0, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        *s++ = c;
        }   //end for
    if (c == '\n') {
        *s++ = c;
        i++;
        }
    *s = '\0';
    return i;
    }   //end function getline


/*  spacesplit:  */
int spacesplit(char **words, char *line, int len, int lim) {
    int i, j, spacetoken;
    char *temp;

    i = j = spacetoken = 0;
    temp = *words = (char *) malloc(len + 1);

    for (i = 0; i < lim && *line != '\0'; line++) {

        if (*line != ' ' && *line != '\t' && *line != '\n') {
            //*(*words)++ = *line;    //wrong: change the real value;
            *temp++ = *line;
            j++;
            spacetoken = 0;
            }
        //space
        else {
            //a new space, last character is not space
            if (spacetoken == 0) {
                //end of current word
                //**words = '\0';    //wrong: change the real value to '\0';
                *temp = '\0';
                j++;
                //free((void *) (temp + 1));    //wrong: memory dump
                //free((void *) temp);  //wrong:
                free((void *) *words);
                *words = (char *) malloc (j);
                //next word
                i++;
                if (*line != '\n') {
                    words++;
                    temp = *words = (char *) malloc(len + 1);
                    }
                }   //end if space
            spacetoken = 1;
            }
        }   //end for

    return i;
    }   //end function spacesplit



/*  hash: form hash value for string s  */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
        }   //end for
    return hashval % HASHSIZE;
    }   //end function hash

/*  lookup: look for s in hashtab  */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            /*  found  */
            return np;
            }   //end if
        }   //end for
    /*  not found  */
    return NULL;
    }   //end function hash


/*
install block:
    intall uses lookup to determine whether the name being installed is already present;
if so, the new definition will supersede the old one. other wise, a new entry is created.
install returns NULL if for any reason there is no room for a new entry.
*/

struct nlist *lookup(char *);
char *strdup(char *);

/*  install: put(name, defn) in hashtab  */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    /*  not found  */
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        /*  name duplicate  */
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
            }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
        }
    /*  already there  */
    else {
        /*  free previous defn  */
        free((void *) np->defn);
        }   //en if

    /*  defn replace text duplicate  */
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
        }   //end if
    return np;
    }   //en function install


/*  make a duplicate of s  */
char *strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1);
    if (p != NULL) {
        strcpy(p, s);
        }   //end if

    return p;
    }   //end function


/*  undefine block: return 0 if not found, else return 1  */
int undefine(char *name) {
    int cond, hashval;
    struct nlist *last, *np;

    hashval = hash(name);
    //last is old point
    last = np = NULL;
    for (np = hashtab[hashval]; np != NULL; last = np, np = np->next) {
        //found name
        if ((cond = strcmp(np->name, name)) == 0) {
            //first point
            if (last == NULL) {
                hashtab[hashval] = np->next;
                }
            //middle point
            else {
                last->next = np->next;
                }
            //free memory
            free((void *) np->defn);
            free((void *) np->name);
            free((void *) np);
            return 1;
            }   //end if cond == 0
        }   //end for

    //not found
    return 0;
    }   //end function undefine
