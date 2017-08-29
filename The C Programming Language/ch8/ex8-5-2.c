/**************************************************************
* Name     :  ex8-5-2.c
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月1日
**************************************************************/

/*
version 0.1:
    not completed.
    error: when read the opened directory, return -1.
*/

/*
example: listing directories
    in unix system, a directory is just a file that contains a list of filenames and some
indication of where they are located. the "location" is an index into another table called the
"inode list". a directory entry generally consists of only two items, the filename and an inode
number.

stat: take a filename and return all of the information in the inode for that file, or -1 if
there is an error.
    char *name;
    struct stat stbuf;
    int stat(char *, struct stat *);
    stat(name, &stbuf);
    fills the structure stbuf with the inode information for the file name.

    //  inode information returned by stat  //
    struct stat {
        //  device of inode  //
        dev_t st_dev;
        //  inode number  //
        ino_t st_ino;
        //  mode bits  //
        short st_mode;
        //  number of links to file  //
        short st_nlink;
        //  //
        //  owners user id  //
        short st_uid;
        //  owner group id  //
        short st_gid;
        //  for special files  //
        dev_t st_rdev;
        //  file size in characters  //
        off_t st_size;
        //  time last accessed  //
        time_t st_atime;
        //  time last modified  //
        time_t st_mtime;
        //  time originally created  //
        time_t st_ctime;
        };

    //  type of file;  //
    #define S_IFMT 0160000
    //  directory  //
    #define S_IFDIR 0040000
    //  character special  //
    #define S_IFCHR 0020000
    //  block special  //
    #define S_IFBLK 0060000
    //  regular  //
    #define S_IFREG 0010000


*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "syscalls.h"
/*  flags for read and write  */
#include <fcntl.h>
/*  typedefs  */
#include <sys/types.h>
/*  structure returned by stat  */
#include <sys/stat.h>
#include "dirent.h"


//  longest filename component; system dependent  //
//#define NAME_MAX 14

//  portable directory entry  //
typedef struct {
    //  inode number  //
    long ino;
    //  name + '\0' terminator  //
    char name[NAME_MAX+1];
    } Dirent;

//  minimal DIRE no buffering, etc.  //
typedef struct {
    //  file descriptor for the directory  //
    int fd;
    //  the directory entry  //
    Dirent d;
    } DIRE;

DIRE *opendire(char *dirname);
Dirent *readdire(DIRE *dfd);
void closedire(DIRE *dfd);

/*  print file name  */
void fsize(char *);

int main(int argc, char **argv) {

    if (argc == 1) {
        /*  default: current directory  */
        fsize(".");
        }
    else {
        while (--argc > 0) {
            fsize(*++argv);
            }   //end while
        }   //end if (argc == 1)

    return 0;
    }   //end function main


/*  fsize block  */
//int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/*  fsize: print the file size and file name of file "name"  */
void fsize(char *name) {

    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
        }   //end if stat == -1

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        printf("haha, success\n");
        dirwalk(name, fsize);
        }   // end if stbuf.st_mode

    printf("%8ld %s\n", stbuf.st_size, name);
    }   //end function fsize


#define MAX_PATH 1024

/*  dirwalk: apply fcn to all files in dir  */
void dirwalk(char *dir, void (*fcn)(char *)) {

    char name[MAX_PATH];
    Dirent *dp;
    DIRE *dfd;


    if ((dfd = opendire(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
        }
    printf("dir is %s\n", dir);
    while ((dp = readdire(dfd)) != NULL) {
        printf("dir = %s, dp->name = %s\n", dir, dp->name);
        /*  skip self and parent  */
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0) {
            continue;
            }   //end if strcmp
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
            }
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
            }   //end if strlen
        }   //end while

    closedire(dfd);
    }   //end function dirwalk


/*  opendire, readdire, closedire blocks  */
#ifndef DIRSIZ
#define DIRSIZ 14
#endif
//  directory entry  //
struct direct {
    //  inode number  //
    ino_t d_ino;
    //  long name does not have '\0'  //
    char d_name[DIRSIZ];
    };

int fstat(int fd, struct stat *);

/*  opendire: open a directory for readdire calls  */
DIRE *opendire(char *dirname) {
    int fd;
    struct stat stbuf;
    DIRE *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 \
        || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIRE *) malloc(sizeof(DIRE))) == NULL)
        {
        return NULL;
        }   //end if

    dp->fd = fd;
    return dp;
    }   //end function opendire



/*  closedire: close directory opened by opendire  */
/*  local directory structure  */
#include <sys/dir.h>

void closedire(DIRE *dp) {
    if (dp) {
        close(dp->fd);
        free(dp);
        }
    }   //end function closedire


/*  readdire: read directory entries in sequence  */
Dirent *readdire(DIRE *dp) {
    /*  local directory structure  */
    struct direct dirbuf;
    /*  return portable structure  */
    static Dirent di;
    printf("fd = %d, read = %d\n", dp->fd, read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)));

    /*  error: read return -1 when run  */
    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
    //while (read(dp->fd, dirbuf.d_name, DIRSIZ) == sizeof(dirbuf.d_name)) {
        /*  slot not in use  */
        if (dirbuf.d_ino == 0) {
            continue;
            }
        di.ino = dirbuf.d_ino;
        strncpy(di.name, dirbuf.d_name, DIRSIZ);
        /*  ensure termination*/
        di.name[DIRSIZ] = '\0';
        return &di;
        }   //end while

    //printf("dirbuf = %s\n", dirbuf.d_name);
    return NULL;
    }   //end function Dirent

