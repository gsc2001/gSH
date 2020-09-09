/****************************************************
author: gsc2001
brief: history implementation
*****************************************************/
#include "globals.h"

#ifndef __HIST_H
#define __HIST_H

#define HISTORY_SZ 20

// position to add history to in the array
int hpos;
char *histFile;

// the history list
char *histList[HISTORY_SZ];

// filename which stores history

// load old history and perform intializing steps
void loadHistory();

// add a command to history
void addToHistory(char *command);

// history command executor
void historyExec(Command c);

// history implementation
void history(int max_n);

// save history to file for future loading
void saveHistory();

#endif // __HIST_H