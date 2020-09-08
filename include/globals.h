/****************************************************
    author: gsc2001
    brief: file with header files
           and global struct definations
*****************************************************/
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX_LEN 1024
#define PROC_LIST_SZ 20

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
    char *command_str;
    int bg;
} Command;

typedef struct ParsedCommands
{
    int n;
    Command *commands;
} ParsedCommands;

typedef struct Process
{
    char *name;
    pid_t id;
} Process;

char *HOME;

Process procList[PROC_LIST_SZ];

#endif // __GLOBAL_H