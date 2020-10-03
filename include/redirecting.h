/****************************************************
author: gsc2001
brief: redirection handling
*****************************************************/
#include "globals.h"
#ifndef __REDIRECT_H
#define __REDIRECT_H
int stdinSave, stdoutSave, rfd, wfd;
void redirectBegin(Command c);
void redirectRestore();
#endif // __REDIRECT_H