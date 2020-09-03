#include "sysCommand.h"
#include "errorHandler.h"

void execSys(Command c)
{
    int nArgs = c.argc + 1;
    if (c.flags)
        nArgs += strlen(c.flags);
    char **argv = (char **)malloc(nArgs * sizeof(char *));
    int i = 0;
    argv[i++] = strtok(c.command_str, " ");
    while ((argv[i] = strtok(NULL, " ")))
    {
        i++;
    }
    // fork
    pid_t forkReturn = handleSyscallint(fork(), "Error forking");

    if (forkReturn == 0)
    {
        // child process
        handleSyscallint(execvp(argv[0], argv), argv[0]);
    }
    else
    {
        int status;
        wait(&status);
        // printf("hii\n");
    }
}