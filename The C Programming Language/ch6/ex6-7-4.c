/**************************************************************
* Name     :  ex6-7-4.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: bit-field
    A bit-field, or field for short, is  a set of adjacent bits whthin a single
implementation-defined storage unit that we will call a "word".

*/


//The number must be powers of two.
#define KEYWORD 01
#define EXTERNAL 02
#define STATIC 04

enum {KEYWORD = 01, EXTERNAL = 02, STATIC = 04};

//turn on the EXTERNAL and STATIC bits in flags
flags |= EXTERNAL | STATIC;
//turn off
flags &= !(EXTERNAL | STATIC);
//true if turn off
if ((flags & (EXTERNAL | STATIC)) == 0)

//the symbol table #defines above could be replaced by the definition of three fields:
struct {
    //the number 1 following the : represents the field width in bits
    unsigned int is_keyword : 1;
    unsigned int is_extern : 1;
    unsigned int is_static : 1;
    } flags;
//reference as other structure members
flags.is_keyword;
flags.is_extern;

//turn bits on
flags.is_extern = flags.is_static = 1;
//turn bits off
flags.is_extern = flags.is_static = 0;
//
if (flags.is_extern == 0 && flags.is_static == 0)
