/****************************************************
author: gsc2001
brief: kjob implementation
*****************************************************/
#include "globals.h"

#ifndef __KJOB_H
#define __KJOB_H

// kjob executor
void kjobExec(Command c);

// kjob implementation
void kjob(int jobNo, int sig);

#endif // __KJOB_H