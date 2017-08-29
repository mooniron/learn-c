/**************************************************************
* Name     :  ex6-7-3.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月25日
**************************************************************/


/*
example: unions
    union-name.member
    union-pointer->member
union is a kind of structures.
*/

union u_tag {
    int ival;
    float fval;
    char *sval;
    } u;

if (utype == INT) {
    printf("%d\n", u.ival);
    }
else if (utype == FLOAT) {
    printf("%f\n", u.fval);
    }
else if {
    printf("%s\n", u.sval);
    }
else {
    printf("bad type %d in utype\n", utype);
    }

struct {
    char *name;
    int flags;
    int utype;
    union {
        int ival;
        float fval;
        char *sval;
        } u;
    } symtab[NSYM];

symtab[i].u.ival;
//first character of the string sval
*symtab[i].u.sval;
symtab[i].u.sval[0];
