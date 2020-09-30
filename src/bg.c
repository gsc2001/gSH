#include "bg.h"
#include "utils.h"
#include "processList.h"

void bgExec(Command c)
{
    if (!c.argc || c.argc > 1 || noOfFlags(c.args, c.argc))
        fprintf(stderr, "bg takes exaclty 1 argument and no flags; Usage bg job_no\n");
    else
        bg(atoi(c.args[0]));
}

void bg(int job_no)
{
    if (job_no <= 0)
    {
        fprintf(stderr, "job number should be > 0\n");
        return;
    }
    Process p = findProcessJobNo(job_no);
    if (p.name == NULL)
    {
        fprintf(stderr, "Process with job number %d not found in background\n", job_no);
        return;
    }
    kill(p.id, SIGCONT);
}
