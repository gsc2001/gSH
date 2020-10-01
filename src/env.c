#include "env.h"
#include "utils.h"
#include "errorHandler.h"

void setenvExec(Command c)
{
    if (!c.argc || c.argc > 2 || noOfFlags(c.args, c.argc))
        fprintf(stderr, "Wrong format for setenv; Usage setenv var [value]\n");
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
    if (!(c.argc == 1) || noOfFlags(c.args, c.argc))
        fprintf(stderr, "Wrong format for setenv; Usage setenv var [value]\n");
    else
        handleSyscallint(unsetenv(c.args[0]), "Error unsetting env variable");
}