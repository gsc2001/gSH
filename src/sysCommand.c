#include "sysCommand.h"
#include "errorHandler.h"
#include "list.h"
#include "utils.h"

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
            Process p;
            initProcess(&p, forkReturn, argv[0]);
            insertProcess(p);

            // print pid of child
            printf("pid %d\n", forkReturn);

            // cleanup
            free(p.name);
        }
        else
            waitpid(forkReturn, &status, WUNTRACED);
    }
}