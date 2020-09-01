/****************************************************
    author: gsc2001
    brief: file with header files
           and global struct definations
*****************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX_LEN 1024
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

typedef struct Command
{
    int argc;
    char *cmd;
    char **args;
    char *flags;
} Command;

typedef struct ParsedCommands
{
    int n;
    Command *commands;
} ParsedCommands;

char *HOME;

#endif // __GLOBAL_H