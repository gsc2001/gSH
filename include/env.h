/****************************************************
author: gsc2001
brief: setenv and unsetenv implementation
*****************************************************/
#include "globals.h"

#ifndef __ENV_H
#define __ENV_H

// setenv executor
void setenvExec(Command c);

// unsetenv executor
void unsetenvExec(Command c);

#endif // __ENV_H