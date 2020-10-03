#include "redirecting.h"
#include "errorHandler.h"

void redirectBegin(Command c)
{
    stdinSave = -1;
    stdoutSave = -1;

    if (c.inp)
    {
        rfd = handleSyscallint(open(c.inp, O_RDONLY), "Error opening inp file");
        if (rfd >= 0)
        {
            stdinSave = dup(STDIN_FILENO);
            dup2(rfd, STDIN_FILENO);
        }
    }
    if (c.out)
    {
        if (c.append)
            wfd = handleSyscallint(open(c.out, O_CREAT | O_WRONLY | O_APPEND, 0644), "Error opening output file");
        else
            wfd = handleSyscallint(open(c.out, O_CREAT | O_WRONLY | O_TRUNC, 0644), "Error opening output file");

        if (wfd >= 0)
        {
            stdoutSave = dup(STDOUT_FILENO);
            dup2(wfd, STDOUT_FILENO);
        }
    }
}

void redirectRestore()
{
    if (stdinSave >= 0)
    {
        dup2(stdinSave, STDIN_FILENO);
        close(rfd);
        close(stdinSave);
    }
    if (stdoutSave >= 0)
    {
        dup2(stdoutSave, STDOUT_FILENO);
        close(wfd);
        close(stdoutSave);
    }
}