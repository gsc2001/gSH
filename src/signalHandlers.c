#include "signalHandlers.h"
#include "prompt.h"
#include "processList.h"

void sigchldHandler(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid <= 0)
        return;

    Process p = findProcess(pid);
    int found = p.name != NULL;

    if (found)
    {
        // remove the proces from list
        removeProcess(pid);
    }
    exitCode = -1;
    char *exitType = (char *)malloc(15);

    strcpy(exitType, ((WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) ? "normally" : "abnormally"));
    printf("\n%s with pid %d exited %s\n", found ? p.name : "Process", p.id, exitType);

    char *prompt = get_prompt();
    printf("%s", prompt);
    fflush(stdout);

    free(prompt);
    free(p.name);
}

void sigintHandler(int sig)
{
    char *prompt = get_prompt();
    printf("\n%s", prompt);
    fflush(stdout);
}

void sigtstpHandler(int sig)
{
    char *prompt = get_prompt();
    printf("\n%s", prompt);
    fflush(stdout);
}
