/****************************************************
author: gsc2001
brief: bg command implementation
*****************************************************/
#include "globals.h"

#ifndef __BG_H
#define __BG_H
// bg command executor
void bgExec(Command c);

// bg command implementation
void bg(int job_no);
#endif // __BG_H