#include "sysCommand.h"
#include "errorHandler.h"

void execSys(Command c)
{
    int nArgs = c.argc + 1;
    if (c.flags)
        nArgs += strlen(c.flags);
    char *argv[nArgs];
    int i = 0;
    char *token = strtok(c.command_str, " ");

    // very very bad way, need to change this
    while (token && strcmp(token, "&"))
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

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
                    bgProcList[i].name = (char *)malloc(strlen(c.command_str) + 1);
                    bgProcList[i].name[0] = '\0';
                    strcpy(bgProcList[i].name, c.command_str);
                    break;
                }
            }
        }
        else
            waitpid(forkReturn, &status, WUNTRACED);
    }
}