#include "cd.h"
#include "utils.h"
#include "errorHandler.h"

void cdExec(Command c)
{
    if (c.argc > 1)
        fprintf(stderr, "cd: too many args; Usage: cd dir\n");
    else if (noOfFlags(c.args, c.argc))
        fprintf(stderr, "cd: no flags allowed; Usage: cd dir\n");
    else if (c.argc == 0)
        cd(HOME);
    else
        cd(c.args[0]);
}

void cd(char *path)
{
    path = replaceTilda(path);
    handleSyscallint(chdir(path), path);
}