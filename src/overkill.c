#include "overkill.h"
#include "processList.h"

void overkillExec(Command c)
{
    exitCode = 0;
    if (c.argc)
    {
        fprintf(stderr, "overkill takes no args; Usage overkill\n");
        exitCode = 1;
    }
    else
    {
        killAllProcesses();
    }
}