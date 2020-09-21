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
        setpgid(0, 0);
        handleSyscallint(execvp(argv[0], argv), argv[0]);
        exit(EXIT_FAILURE);
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
        {
            // make the forground process group foreground
            setpgid(forkReturn, 0);
            tcsetpgrp(0, forkReturn);

            // as shell will be removed from foreground so mute its call for I/O
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            waitpid(forkReturn, &status, WUNTRACED);

            // shell to foreground now
            tcsetpgrp(0, getpgid(0));

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
}