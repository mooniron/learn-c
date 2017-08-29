/**************************************************************
* Name     :  ex6-1-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月16日
**************************************************************/


/*
example: basics of structure
example: structures and functions
struct: a new type declaration like int, char etc
*/


#include <stdio.h>


/*  basics of structure  */

    struct point {int x; int y};
    struct point pt = {0, 0};
    printf("%d, %d\n", pt.x, pt.y);

    /*  calculate the distance of pt to (0, 0)  */
    double dist, sqrt(double);
    dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);

    /*  example of rectangle: a pair of opposite point  */
    struct rect {struct point pt1; struct point pt2};
    struct rect screen;


/*  structures and functions  */
/*  makepoint: make a point from x and y components  */
struct point makepoint(int x, int y) {
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
    }   //end function makepoint

/*  addpoints: add two points  */
struct addpoint(struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;

    return p1;
    }   //end function addpoint

/*  ptinrect: return 1 if p in r, 0 if not  */
int ptinrect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x <= r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
    }   //end function ptinrect


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/*  canonrect: canonicalize coordinates of rectangle  */
struct rect canonrect(struct rect r) {
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
    }   //end function canonrect

/*  pointer  */
struct point origin, *pp;
pp = &origin;
printf("origin is (%d, %d)\n", (*pp).x, (*pp).y);
printf("origin is (%d, %d)\n", pp->x, pp->y);
struct rect r, *rp = &r;
//equivalent
r.pt1.x;
rp->pt1.x;
(r.pt1).x;
(rp->pt1).x;
//
struct {
    int len;
    char *str;
    } *p;

++p->len == ++(p->len);
