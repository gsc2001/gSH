/****************************************************
author: gsc2001
brief: parse input string  
*****************************************************/
#include "globals.h"

#ifndef __PARSE_H
#define __PARSE_H

// Parses inp for commands seperrated by ;
ParsedCommands parse(char *inp);

// Parse Command from command string
Command parseCommand(char *command_);

// Parse PipedCommands from pipedCommands string
PipedCommands parsePiped(char *pipedCommands);

#endif // __PARSE_H