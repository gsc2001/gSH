/****************************************************
author: gsc2001
brief: some basic utility functions
*****************************************************/
#include "globals.h"

#ifndef __UTILS_H
#define __UTILS_H

// replace the home dir string with ~
char *replaceHomeDir(char *);

// replace Tilda with HOME location
char *replaceTilda(char *);

// replace tabs with spaces
void replaceTabs(char *str);

// check if a args list has flags or not
int noOfFlags(char **args, int n);

#endif // __UTILS_H