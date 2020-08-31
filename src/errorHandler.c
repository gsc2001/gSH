#include "globals.h"
#include "errorHandler.h"

void handleSyscallint(int returnValue, const char *msg)
{
    if (returnValue < 0)
        perror(msg);
}

void handleSyscallchar(char *returnValue, const char *msg)
{
    if (!returnValue)
        perror(msg);
}