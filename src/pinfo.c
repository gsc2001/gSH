#include "pinfo.h"
#include "errorHandler.h"
#include "utils.h"

void pinfoExec(Command c)
{
    if (noOfFlags(c.args, c.argc))
        fprintf(stderr, "pinfo: Flags not allowed; Usage pinfo [pid]\n");
    else if (c.argc == 0)
        pinfo("self");
    else if (c.argc == 1)
        pinfo(c.args[0]);
    else
        fprintf(stderr, "pinfo: Too many arguments; Usage pinfo [pid]\n");
}

void pinfo(char *pid)
{
    char *procDir = (char *)malloc(MAX_LEN);
    sprintf(procDir, "/proc/%s", pid);

    char *statusFile = (char *)malloc(MAX_LEN);
    sprintf(statusFile, "%s/status", procDir);

    FILE *f = fopen(statusFile, "r");
    if (!f)
    {
        fprintf(stderr, "Process with pid %s not found", pid);
        free(procDir);
        free(statusFile);
        return;
    }
    char *state = (char *)malloc(5);
    char *vmSize = (char *)malloc(MAX_LEN);
    char *pid_ = (char *)malloc(MAX_LEN);
    char *buf = (char *)malloc(MAX_LEN);
    int i = 1;

    while ((fgets(buf, MAX_LEN - 1, f)))
    {
        if (i == 3)
        {
            strtok(buf, " \t");
            strcpy(state, strtok(NULL, " \t"));
        }
        else if (i == 6)
        {
            strtok(buf, " \t");
            strcpy(pid_, strtok(NULL, " \t"));
            pid_[strlen(pid_) - 1] = '\0';
        }
        else if (i == 18)
        {
            strtok(buf, " \t");
            strcpy(vmSize, strtok(NULL, " \t"));
            break;
        }
        i++;
    }
    if (getpgid(atoi(pid_)) == tcgetpgrp(0))
        strcat(state, "+");

    char *executableFile = (char *)malloc(MAX_LEN);
    sprintf(executableFile, "%s/exe", procDir);
    char *exec = (char *)malloc(MAX_LEN);
    int sz = handleSyscallint(readlink(executableFile, exec, MAX_LEN - 1), "reading exectuble link");
    exec[sz] = '\0';
    exec = replaceHomeDir(exec);
    // output
    printf("pid -- %s\n", pid_);
    printf("Process Status -- %s\n", state);
    printf("memory -- %s\n", vmSize);
    printf("Executable file -- %s\n", exec);

    // final cleanup
    free(procDir);
    free(executableFile);
    free(exec);
    free(state);
    free(vmSize);
    free(buf);
}