/**************************************************************
* Name     :  ex8-6-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月5日
**************************************************************/


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


/*  for alignment to long boundary  */
typedef long Align;
/*  block header  */
union header {
    struct {
        /*  next block if on free list  */
        union header *ptr;
        /*  size of this block  */
        unsigned size;
        } s;
    /*  force alignment of blocks  */
    Align x;
    };
typedef union header Header;

/*  empty list to get started  */
static Header base;
/*  start of free list  */
static Header *freep = NULL;

/*  malloc: general-purpose storage allocator  */
void *malloc(unsigned nbytes) {
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(header) + 1;

    /*  no free list yet  */
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
        }   //end if

    for (p = prevp->s.ptr; ;prevp = p, p = p->s.ptr) {
        /*  big enough  */
        if (p->s.size >= nunits) {
            /*  exactly  */
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
                }
            /*  allocate tail end  */
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
                }   //end if
            freep = prevp;
            return (void *)(p + 1);
            }   //end if
        /*  wrapped around free list  */
        if (p == freep) {
            if ((p = morecore(nunits)) == NULL) {
                /*  none left  */
                return NULL;
                }
            }   //end if p ==
        }   //end for
    }   //end function malloc


/*  morecore block  */
/*minimum #units to request  */
#define NALLOC 1024

void free(void *);

/*  morecore: ask system for more memory  */
static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
        }   //end if
    cp = sbrk(nu * sizeof(Header));
    /*  no space at all  */
    if (cp == (char *) -1) {
        return NULL;
        }
    up = (Header *) cp;
    up->s.size = nu;
    free((void *) (up + 1));
    return freep;
    }   //end function morecore


/*  free: put block ap in free list  */
void free(void *ap) {
    Header *bp, *p;
    /*  pointer to header  */
    bp = (Header *) ap - 1;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        /*  freed block at start or end of arena  */
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
            }
        }   //end for

    /*  join to upper nbr  */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
        }
    else {
        bp->s.ptr = p->s.ptr;
        }   //end if
    /*  join to lower nbr  */
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
        }
    else {
        p->s.ptr = bp;
        }
    freep = p;
    }   //end function free
