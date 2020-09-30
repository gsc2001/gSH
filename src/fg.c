#include "fg.h"
#include "utils.h"
#include "processList.h"

void fgExec(Command c)
{
    if (!c.argc || noOfFlags(c.args, c.argc) || c.argc > 1)
        fprintf(stderr, "Wrong number of arguments; Usage fg job_no\n");
    else
        fg(atoi(c.args[0]));
}

void fg(int job_no)
{
    if (job_no <= 0)
    {
        fprintf(stderr, "Job number should be > 0\n");
        return;
    }
    Process p = findProcessJobNo(job_no);
    int status;

    if (p.name == NULL)
    {
        fprintf(stderr, "job number %d not found in background\n", job_no);
        return;
    }
    pid_t pid = p.id;
    setpgid(pid, 0);

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(0, pid);

    kill(pid, SIGCONT);

    waitpid(pid, &status, WUNTRACED);

    tcsetpgrp(0, getpgid(0));

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    removeProcess(pid);

    if (WIFSTOPPED(status))
        insertProcess(p);
}
