#include "pinfo.h"
#include "errorHandler.h"
#include "utils.h"

void pinfoExec(Command c)
{
    exitCode = 0;
    if (noOfFlags(c.args, c.argc))
    {
        fprintf(stderr, "pinfo: Flags not allowed; Usage pinfo [pid]\n");
        exitCode = 1;
    }
    else if (c.argc == 0)
        pinfo("self");
    else if (c.argc == 1)
        pinfo(c.args[0]);
    else
    {
        fprintf(stderr, "pinfo: Too many arguments; Usage pinfo [pid]\n");
        exitCode = 1;
    }
}

void pinfo(char *pid)
{
    char *procDir = (char *)malloc(MAX_LEN);
    sprintf(procDir, "/proc/%s", pid);

    char *statusFile = (char *)malloc(MAX_LEN);
    sprintf(statusFile, "%s/stat", procDir);

    FILE *f = fopen(statusFile, "r");
    if (!f)
    {
        fprintf(stderr, "Process with pid %s not found\n", pid);
        free(procDir);
        free(statusFile);
        exitCode = 1;
        return;
    }
    char *state = (char *)malloc(5);
    char *vmSize = (char *)malloc(MAX_LEN);
    char *pid_ = (char *)malloc(MAX_LEN);
    char *buf = (char *)malloc(MAX_LEN);
    int pgrp, tpgid;
    int i = 1;

    while (fscanf(f, "%s", buf) != EOF)
    {
        if (i == 3)
            strcpy(state, buf);
        else if (i == 1)
            strcpy(pid_, buf);
        else if (i == 5)
            pgrp = atoi(buf);
        else if (i == 8)
            tpgid = atoi(buf);
        else if (i == 23)
        {
            strcpy(vmSize, buf);
            break;
        }
        i++;
    }
    if (pgrp == tpgid)
        strcat(state, "+");

    char *executableFile = (char *)malloc(MAX_LEN);
    sprintf(executableFile, "%s/exe", procDir);
    char *exec = (char *)malloc(MAX_LEN);
    int sz = handleSyscallint(readlink(executableFile, exec, MAX_LEN - 1), "reading exectuble link");
    if (sz >= 0)
    {
        exec[sz] = '\0';
        exec = replaceHomeDir(exec);
        // output
        printf("pid -- %s\n", pid_);
        printf("Process Status -- %s\n", state);
        printf("memory -- %s\n", vmSize);
        printf("Executable file -- %s\n", exec);
    }
    else
        exitCode = 1;

    // final cleanup
    free(procDir);
    free(executableFile);
    free(statusFile);
    free(exec);
    free(state);
    free(vmSize);
    free(buf);
    free(pid_);
}