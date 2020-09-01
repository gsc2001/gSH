/****************************************************
author: gsc2001
brief: some basic utility functions
*****************************************************/
#ifndef __UTILS_H
#define __UTILS_H

// replace the home dir string with ~
char *replaceHomeDir(char *);

// replace Tilda with HOME location
char *replaceTilda(char *);

// replace tabs with spaces
void replaceTabs(char *str);

#endif // __UTILS_H