/**************************************************************
* Name     :  ex5-4-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年3月6日
**************************************************************/

/*
exercisse 5-4: function version
    strend: return 1 if string t occurs at the end of s, zero otherwise.
*/


/*  strlen: get the length of a string  */
int strlen(char *s) {
    int n = 0;

    while (*s++ != '\0') {
        n++;
        }
    return n;
    }

/*  strcmp: compare s and t, return > 0 if s > t, 0 if s == t, < 0 if s < t  */
int strcmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
            }
        s++;
        t++;
        }
    return *s - *t;
    }

/*  strend: return 1 if string t occiurs at the end of s, zero otherwise  */
int strend(char *s, char *t) {
    int result = 0;
    int size_s = strlen(s);
    int size_t = strlen(t);

    if (size_t <= size_s) {
        /* advance the s pointer to where the string t would have to start in string s */
        s += size_s - size_t;
        /* and make the compare using strcmp */
        if (strcmp(s, t) == 0) {
            result = 1;
            }
        }

    return result;
    }


#include <stdio.h>

int main(void)
{
  char *s1 = "some really long string.";
  char *s2 = "ng.";
  char *s3 = "ng";

  if(strend(s1, s2))
  {
    printf("The string (%s) has (%s) at the end.\n", s1, s2);
  }
  else
  {
    printf("The string (%s) doesn't have (%s) at the end.\n", s1, s2);
  }
  if(strend(s1, s3))
  {
    printf("The string (%s) has (%s) at the end.\n", s1, s3);
  }
  else
  {
    printf("The string (%s) doesn't have (%s) at the end.\n", s1, s3);
  }

  return 0;
}
