#include "signalHandlers.h"
#include "prompt.h"

void sigchldHandler(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid <= 0)
        return;

    Process p;
    p.id = pid;
    p.name = (char *)malloc(MAX_LEN);
    p.name[0] = '\0';

    int found = 0;
    for (int i = 0; i < PROC_LIST_SZ; i++)
    {
        if (bgProcList[i].id == pid)
        {
            bgProcList[i].id = -1;
            strcpy(p.name, bgProcList[i].name);
            free(bgProcList[i].name);
            found = 1;
            break;
        }
    }

    char *exitType = (char *)malloc(15);

    strcpy(exitType, ((WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) ? "normally" : "abnormally"));
    printf("\n%s with pid %d exited %s\n", found ? p.name : "Process", p.id, exitType);

    char *prompt = get_prompt();
    printf("%s", prompt);
    fflush(stdout);

    free(prompt);
    free(p.name);
}