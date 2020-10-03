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
    if (!strcmp(path, "-"))
    {
        if (!lastDir)
        {
            printf("%s\n", HOME);
            return;
        }
        path = lastDir;
        printf("%s\n", path);
    }

    char *cwd = (char *)malloc(MAX_LEN);
    char *wd = handleSyscallchar(getcwd(cwd, MAX_LEN - 1), "Error getting cwd");
    if (wd == NULL)
    {
        free(cwd);
        cwd = NULL;
    }
    int done = handleSyscallint(chdir(path), path);
    if (done == 0 && cwd != NULL)
    {
        if (!lastDir)
            lastDir = (char *)malloc(MAX_LEN);
        strcpy(lastDir, cwd);
        free(cwd);
    }
}