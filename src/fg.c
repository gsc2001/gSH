#include "fg.h"
#include "utils.h"
#include "processList.h"
#include "errorHandler.h"

void fgExec(Command c)
{
    exitCode = 0;
    if (!c.argc || noOfFlags(c.args, c.argc) || c.argc > 1)
    {
        fprintf(stderr, "Wrong number of arguments; Usage fg job_no\n");
        exitCode = 1;
    }
    else
        fg(atoi(c.args[0]));
}

void fg(int job_no)
{
    if (job_no <= 0)
    {
        fprintf(stderr, "Job number should be > 0\n");
        exitCode = 1;
        return;
    }
    Process p = findProcessJobNo(job_no);
    int status;

    if (p.name == NULL)
    {
        fprintf(stderr, "job number %d not found in background\n", job_no);
        exitCode = 1;
        return;
    }
    pid_t pid = p.id;
    setpgid(pid, 0);

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(0, pid);

    if (handleSyscallint(kill(pid, SIGCONT), "fg") < 0)
        exitCode = 1;

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    removeProcess(pid);

    if (WIFSTOPPED(status))
    {
        insertProcess(p);
        exitCode = 1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) == EXIT_FAILURE)
        exitCode = 1;
}
