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
    sprintf(statusFile, "%s/stat", procDir);

    FILE *f = fopen(statusFile, "r");
    if (!f)
    {
        fprintf(stderr, "Process with pid %s not found", pid);
        free(procDir);
        free(statusFile);
        return;
    }

    char *status = (char *)malloc(MAX_LEN); // cleanup at end
    fgets(status, MAX_LEN - 1, f);

    // pid
    char *pid_ = strtok(status, " ");
    strtok(NULL, " ");
    // status
    char *state = strtok(NULL, " ");
    // status cleanup
    free(statusFile);
    fclose(f);

    char *memFile = (char *)malloc(MAX_LEN);
    char *mem = (char *)malloc(MAX_LEN); // cleanup at end
    sprintf(memFile, "%s/statm", procDir);
    f = fopen(memFile, "r");
    fgets(mem, MAX_LEN - 1, f);
    char *vmSize = strtok(mem, " ");

    // mem cleanup
    free(memFile);
    fclose(f);

    char *executableFile = (char *)malloc(MAX_LEN);
    sprintf(executableFile, "%s/exe", procDir);
    char *exec = (char *)malloc(MAX_LEN);
    int sz = handleSyscallint(readlink(executableFile, exec, MAX_LEN - 1), "reading exectuble link");
    exec[sz] = '\0';

    // output
    printf("pid -- %s\n", pid_);
    printf("Process Status -- %s\n", state);
    printf("memory -- %s\n", vmSize);
    printf("Executable file -- %s\n", exec);

    // final cleanup
    free(procDir);
    free(executableFile);
    free(exec);
    free(mem);
    free(status);
}