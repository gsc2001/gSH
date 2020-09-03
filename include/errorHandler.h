/****************************************************
author: gsc2001
brief: utility functions to handle common errors
*****************************************************/
#ifndef __ERROR_H
#define __ERROR_H

// syscalls with int return
int handleSyscallint(int, const char *);

// syscalls with char * return
char *handleSyscallchar(char *, const char *);
#endif // __ERROR_H