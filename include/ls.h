/****************************************************
author: gsc2001
brief: ls implementation
*****************************************************/
#include "globals.h"

#ifndef __LS_H
#define __LS_H

typedef struct LsOpts
{
    int l, a;
} LsOpts;

// execute ls
void lsExec(Command c);

// ls implementation
void ls(char *path, LsOpts lsopts);

#endif // __LS_H