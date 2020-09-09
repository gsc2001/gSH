/****************************************************
    author: gsc2001
    brief: shell core loops
*****************************************************/
#include "globals.h"

#ifndef __SHELL_H
#define __SHELL_H

// init stuff
void init();

// main loop
void repl();

// function while exiting
void byebye();

// Command executor
void execCommand(Command c);

#endif // __SHELL_H