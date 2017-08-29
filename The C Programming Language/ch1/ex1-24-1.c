/**************************************************************
* Name     :  ex1-24-1.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月5日
**************************************************************/


/*
exercise 1-24:
    write a program to check a C program for rudimentary syntax errors like unmatched
parentheses, brackets and braces. don't forget about quotes, both single and double, escape
sequences, and comments. (this program is hard if you do it in full generality.)

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  exercise 1-24  */
struct flag {
    // left count number
    int left;
    // right count number
    int right;
    // left count number when quote mode
    int quoteleft;
    // right count number when quote mode
    int quoteright;
    // left count when comment mode
    int comleft;
    // right count when comment mode
    int comright;
    };

// initialize flag
struct flag paren = {0, 0, 0, 0, 0, 0};
struct flag bracket = {0, 0, 0, 0, 0, 0};
struct flag brace = {0, 0, 0, 0, 0, 0};

int getch(void);
int ungetch(int);
void clearquote();
void clearcomment();

int main() {
    int c;
    /*  quote and comment flags  */
    int escape, quote, comment, quotecom, comquote;

    c = 0;
    escape = quote = comment = quotecom = comquote = 0;

    while ((c = getch()) != EOF) {
        // escape flag
        if (c == '\\') {
            escape = 1;
            continue;
            }

        /*  set flags  */
        // quote flag
        if (escape == 0 && c == '"') {
            if (comment == 1) {
                comment = 0;
                comquote = 1;
                }
            else if (quotecom == 1) {
                quotecom = 0;
                clearquote();
                clearcomment();
                }
            else if (comquote == 1) {
                comquote = 0;
                comment = 1;
                clearquote();
                }
            else if (quote == 1) {
                quote = 0;
                clearquote();
                }
            else {
                quote = 1;
                }
            continue;
            }
        else if (escape == 0 && c == '/') {
            // is a comment flag
            if ((c = getch()) == '*') {
                if (quote == 1) {
                    quote = 0;
                    quotecom = 1;
                    }
                else if (quotecom == 0 && comquote == 0)
                    comment = 1;
                    }
            // not a valid value
            else {
                ungetch(c);
                }
            continue;
            }   // end if c = /
        else if (escape == 0 && c == '*' && (comment == 1 || quotecom == 1 || comquote == 1)) {
            if ((c = getch()) != '/') {
                ungetch(c);
                continue;
                }
            // is an comment end flag
            if (comment == 1) {
                comment = 0;
                clearcomment();
                }
            else if (quotecom == 1) {
                quotecom = 0;
                quote = 1;
                clearcomment();
                }
            else if (comquote == 1) {
                comquote = 0;
                clearcomment();
                clearquote();
                }
            continue;
            }   //end if c == *

        // set counts
        switch(c) {
            case '(':
                if (comment == 1 || quotecom == 1) {
                    paren.comleft++;
                    }
                else if (quote == 1 || comquote == 1) {
                    paren.quoteleft++;
                    }
                else {
                    paren.left++;
                    }
                break;
            case ')':
                if (comment == 1 || quotecom == 1) {
                    paren.comright++;
                    }
                else if (quote == 1 || comquote == 1) {
                    paren.quoteright++;
                    }
                else {
                    paren.right++;
                    }
                break;
            case '[':
                if (comment == 1 || quotecom == 1) {
                    bracket.comleft++;
                    }
                else if (quote == 1 || comquote == 1) {
                    bracket.quoteleft++;
                    }
                else {
                    bracket.left++;
                    }
                break;
            case ']':
                if (comment == 1 || quotecom == 1) {
                    bracket.comright++;
                    }
                else if (quote == 1 || comquote == 1) {
                    bracket.quoteright++;
                    }
                else {
                    bracket.right++;
                    }
                break;
            case '{':
                if (comment == 1 || quotecom == 1) {
                    brace.comleft++;
                    }
                else if (quote == 1 || comquote == 1) {
                    brace.quoteleft++;
                    }
                else {
                    brace.left++;
                    }
                break;
            case '}':
                if (comment == 1 || quotecom == 1) {
                    brace.comright++;
                    }
                else if (quote == 1 || comquote == 1) {
                    brace.quoteright++;
                    }
                else {
                    brace.right++;
                    }
                break;
            default:
                break;
            }   //end switch

        // initialize escape
        escape = 0;
        }   // end while

    // add non-zero quote count and comment count
    paren.left += paren.quoteleft + paren.comleft;
    paren.right += paren.quoteright + paren.comright;
    bracket.left += bracket.quoteleft + bracket.comleft;
    bracket.right += bracket.quoteright + bracket.comright;
    brace.left += brace.quoteleft + brace.comleft;
    brace.right += brace.quoteright + brace.comright;

    if (paren.left != paren.right) {
        fprintf(stderr, "error: there is unmatched parenthese\n");
        }
    if (bracket.left != bracket.right) {
        fprintf(stderr, "error: there is unmatched bracket\n");
        }
    if (brace.left != brace.right) {
        fprintf(stderr, "error: there is unmatched brace\n");
        }
    // all match
    if (paren.left == paren.right && bracket.left == bracket.right && brace.left == brace.right)
        {
        printf("all matched\n");
        }

    return 0;
    }   //end function main


/*  getch block  */
static int getflag = 0;
static int ch = 0;

int getch() {
    if (getflag > 0) {
        getflag = 0;
        return ch;
        }
    else {
        return getchar();
        }
    }   //end function getch

int ungetch(int c) {
    if (getflag == 0) {
        ch = c;
        getflag = 1;
        return ch;
        }
    else {
        return -1;
        }
    }   //end function ungetch


/*  exercise 1-24: clear mode  */

void clearquote() {
    paren.quoteleft = 0;
    paren.quoteright = 0;
    bracket.quoteleft = 0;
    bracket.quoteright = 0;
    brace.quoteleft = 0;
    brace.quoteright = 0;
    }   //end function clearquote


void clearcomment() {
    paren.comleft = 0;
    paren.comright = 0;
    bracket.comleft = 0;
    bracket.comright = 0;
    brace.comleft = 0;
    brace.comright = 0;
    }   //end function clearcomment
