#include "globals.h"
#include "errorHandler.h"

int handleSyscallint(int returnValue, const char *msg)
{
    if (returnValue < 0)
    {
        perror(msg);
        exitCode = 1;
    }

    return returnValue;
}

char *handleSyscallchar(char *returnValue, const char *msg)
{
    if (!returnValue)
    {
        perror(msg);
        exitCode = 1;
    }
    return returnValue;
}