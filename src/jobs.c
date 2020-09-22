#include "jobs.h"
#include "processList.h"

void jobsExec(Command c)
{
    if (c.argc)
        fprintf(stderr, "jobs command takes no args; Usage jobs\n");
    else
        jobs();
}

void jobs()
{
    printProcesses();
}