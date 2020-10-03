#include "kjob.h"
#include "errorHandler.h"
#include "utils.h"
#include "processList.h"

void kjobExec(Command c)
{
    exitCode = 0;
    if (c.argc != 2 || noOfFlags(c.args, c.argc))
    {
        fprintf(stderr, "Wrong format; Usage kjob jobNo sigNo\n");
        exitCode = 1;
    }
    else
    {
        kjob(atoi(c.args[0]), atoi(c.args[1]));
    }
}

void kjob(int jobNo, int sig)
{
    Process p = findProcessJobNo(jobNo);
    if (p.name == NULL)
    {
        fprintf(stderr, "job %d not found\n", jobNo);
        exitCode = 1;
        return;
    }
    handleSyscallint(kill(p.id, sig), "kjob");
}