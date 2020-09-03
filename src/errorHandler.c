#include "globals.h"
#include "errorHandler.h"

int handleSyscallint(int returnValue, const char *msg)
{
    if (returnValue < 0)
        perror(msg);
    return returnValue;
}

char *handleSyscallchar(char *returnValue, const char *msg)
{
    if (!returnValue)
        perror(msg);
    return returnValue;
}