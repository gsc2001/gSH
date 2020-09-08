#include "mpwd.h"
#include "errorHandler.h"

void pwdExec(Command c)
{
    if (c.argc || c.flags)
        fprintf(stderr, "pwd: Too many arguments/flags\n");
    else
        pwd();
}

void pwd()
{

    char *cwd = handleSyscallchar(getcwd(NULL, MAX_LEN - 1), "Error getting CWD");
    printf("%s\n", cwd);
    free(cwd);
}