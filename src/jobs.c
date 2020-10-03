#include "jobs.h"
#include "processList.h"

void jobsExec(Command c)
{
    exitCode = 0;
    if (c.argc)
    {
        fprintf(stderr, "jobs command takes no args; Usage jobs\n");
        exitCode = 1;
    }
    else
        jobs();
}

void jobs()
{
    printProcesses();
}