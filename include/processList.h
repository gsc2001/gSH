/****************************************************
author: gsc2001
brief: List data structure implementation
*****************************************************/
#include "globals.h"

#ifndef __LIST_H
#define __LIST_H
typedef struct Node
{
    Process p;
    struct Node *next, *prev;
} Node;

// function to insert a node into the list
void insertProcess(Process p);

// remove a process from list
void removeProcess(pid_t pid);

// get a process with given pid
Process findProcess(pid_t pid);

// get a process with given job number
Process findProcessJobNo(int job_no);

// print processes
void printProcesses();
#endif // __LIST_H