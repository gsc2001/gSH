/****************************************************
author: gsc2001
brief: fg command implementation
*****************************************************/
#include "globals.h"

#ifndef __FG_H
#define __FG_H
// exec fg command
void fgExec(Command c);

// fg implementation
void fg(int job_no);
#endif // __FG_H