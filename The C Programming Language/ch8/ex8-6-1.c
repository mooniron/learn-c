/**************************************************************
* Name     :  ex8-6-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月5日
**************************************************************/


/*
exercise 8-6:
    the standard library function calloc(n, size) returns a pointer to n objects of size size,
with the storage initialized to zero. write calloc, by calling malloc or by modifying it.
*/


/*
example: a storage allocator

malloc: in order of increasing order.
    its free storage is kept as a chain list of free blocks. each block contains a size, a
pointer to the next block, and the space itself. the blocks are kept in order of increasing
storage address, and the last block (highest address) points to the first.
    if a request is made, search the free list to get the first big enough block.

free: in order of decreasing address.
    a search of the free list, to find the proper place to insert the block being freed. if the
block being freed is adjacent to a free block on either side, it is coalesced with it into a
single bigger block, so storage does not become too fragmented.

morecore:
    the function morecore obtains storage from the operating system.

sbrk(n): return a pointer to n more bytes of storage. sbrk returns -1 if there was no space.
*/


#include <stdio.h>
#include <stdlib.h>


void *callocbl(size_t n, size_t size);

int main() {
    int *ip = NULL;
    int i = 0;

    if ((ip = (int *) callocbl(100, sizeof(int))) == NULL) {
        fprintf(stderr, "there is no enough space\n");
        }
    else {
        for (i = 0; i < 100; i++) {
            printf("%p\t", (void *) (ip + i));
            if (i % 7 == 6) {
                printf("\n");
                }
            }
        printf("\n");
        }

    free(ip);
    return 0;
    }   //end function main


void *callocbl(size_t n, size_t size) {
    //void *p;
    return malloc(n * size);
    }   //end function callocbl
