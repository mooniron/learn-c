/**************************************************************
* Name     :  ex5-3-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
example: pointer arithmetic storage allocator
    char *alloc(n): return pointer to n characters
    void afree(char *p): free storage pointed to by p
    storage managed by alloc and afree is a stack, or last-in, first-out 后进先出。
*/

/*
The valid pointer operations:
1.  are assignment of pointers of the same type, adding or subtracting a pointer and an integer;
2.  subtracting or comparing two pointers to members of the same array,
3.  and assigning or comparing to zero.

All other pointer arithmetic is illegal.
1.  It is not legal to add two pointers, or to multiply or divide or shift or mask them;
2.  It is not legal to add float or double to them, or even,except for void *;
3.  It is not legal to assign a pointer of one type to a pointer of another type without a cast.
*/


/*  size of available space  */
#define ALLOCSIZE 10000

/*storage for alloc, visible only for alloc and afree  */
static char allocbuf[ALLOCSIZE];
/*  next free position pointer, the array name is the address of the zeroth element  */
static char *allocp = allocbuf;

/*  return pointer to n characters  */
char *alloc(int n) {
    /*  it fits, enough free room for allocate  */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        /*  old p  */
        return allocp - n;
        }
    /*  not enough room  */
    else {
        /*  zero is never a valid address for data  */
        return 0;
        //return NULL;
        }
    }

/*  free storage pointed to by p  */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
        }
    }

/*  strlen: return length of string s  */
int strlen(char *s) {
    char *p = s;

    while (*p != '\0') {
        p++;
        }
    return p - s;
    }
