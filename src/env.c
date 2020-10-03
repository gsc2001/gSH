#include "env.h"
#include "utils.h"
#include "errorHandler.h"

void setenvExec(Command c)
{
    exitCode = 0;
    if (!c.argc || c.argc > 2 || noOfFlags(c.args, c.argc))
    {
        fprintf(stderr, "Wrong format for setenv; Usage setenv var [value]\n");
        exitCode = 1;
    }
    else
    {
        if (c.argc == 1)
            handleSyscallint(setenv(c.args[0], "", 1), "Error setting env variable");
        else
            handleSyscallint(setenv(c.args[0], c.args[1], 1), "Error setting env variable");
    }
}

void unsetenvExec(Command c)
{
    exitCode = 0;
    if (!(c.argc == 1) || noOfFlags(c.args, c.argc))
    {
        fprintf(stderr, "Wrong format for setenv; Usage setenv var [value]\n");
        exitCode = 1;
    }
    else
        handleSyscallint(unsetenv(c.args[0]), "Error unsetting env variable");
}