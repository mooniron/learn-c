/**************************************************************
* Name     :  ex4-14-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月5日
**************************************************************/

/*
example: conditional define
*/

#include <stdio.h>

#ifndef HDR
    #define HDR
    /*  contents of hdr.h go here  */
#endif

#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#else
    #define HDR "default.h"
#endif
#include HDR
