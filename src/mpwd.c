#include "mpwd.h"
#include "errorHandler.h"

void pwdExec(Command c)
{
    exitCode = 0;
    if (c.argc)
    {
        fprintf(stderr, "pwd: Too many arguments/flags\n");
        exitCode = 1;
    }
    else
        pwd();
}

void pwd()
{

    char *cwd = handleSyscallchar(getcwd(NULL, MAX_LEN - 1), "Error getting CWD");
    printf("%s\n", cwd);
    free(cwd);
}