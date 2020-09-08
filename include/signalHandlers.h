/****************************************************
author: gsc2001
brief: signal handlers for signals SIGCHLD
*****************************************************/
#include "globals.h"

#ifndef __SIGNAL_H
#define __SIGNAL_H

// handler for SIGCHLD
void sigchldHandler(int sig);

#endif // __SIGNAL_H