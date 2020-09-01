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
    char *cwd = (char *)malloc(MAX_LEN);
    handleSyscallchar(getcwd(cwd, MAX_LEN), "Error getting CWD");
    printf("%s\n", cwd);
}