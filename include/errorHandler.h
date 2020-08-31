/****************************************************
author: gsc2001
brief: utility functions to handle common errors
*****************************************************/
#ifndef __ERROR_H
#define __ERROR_H

// syscalls with int return
void handleSyscallint(int, const char *);

// syscalls with char * return
void handleSyscallchar(char *, const char *);
#endif // __ERROR_H