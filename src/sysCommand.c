#include "sysCommand.h"
#include "errorHandler.h"

void execSys(Command c)
{
    char *argv[c.argc + 2];

    argv[0] = c.cmd;
    for (int i = 0; i < c.argc; i++)
        argv[i + 1] = c.args[i];
    argv[c.argc + 1] = NULL;

    // fork
    pid_t forkReturn = handleSyscallint(fork(), "Error forking");

    if (forkReturn == 0)
    {
        // child process
        if (c.bg)
            setpgid(0, 0);

        handleSyscallint(execvp(argv[0], argv), argv[0]);
        exit(1);
    }
    else
    {
        int status;
        if (c.bg)
        {
            // find free place
            for (int i = 0; i < PROC_LIST_SZ; i++)
            {
                if (bgProcList[i].id == -1)
                {
                    bgProcList[i].id = forkReturn;
                    bgProcList[i].name = (char *)malloc(strlen(argv[0]) + 1);
                    bgProcList[i].name[0] = '\0';
                    strcpy(bgProcList[i].name, argv[0]);
                    break;
                }
            }
        }
        else
            waitpid(forkReturn, &status, WUNTRACED);
    }
}