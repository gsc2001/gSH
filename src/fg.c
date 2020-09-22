#include "fg.h"
#include "utils.h"
#include "processList.h"

void fgExec(Command c)
{
    if (!c.argc || noOfFlags(c.args, c.argc) || c.argc > 1)
        fprintf(stderr, "Wrong number of arguments; Usage fg [pid]\n");
    else
        fg(atoi(c.args[0]));
}

void fg(pid_t pid)
{
    Process p = findProcess(pid);
    int status;

    if (p.name == NULL)
    {
        fprintf(stderr, "pid [%d] not found in background\n", pid);
        return;
    }
    setpgid(pid, 0);

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(0, pid);

    kill(pid, SIGCONT);

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (WIFEXITED(status))
        removeProcess(pid);
}
