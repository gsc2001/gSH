#include "globals.h"
#include "prompt.h"
#include "utils.h"
#include "errorHandler.h"

char *get_prompt()
{
    char *cwd = handleSyscallchar(getcwd(NULL, 0), "Getting CWD");
    cwd = replaceHomeDir(cwd);
    char *host = (char *)malloc(MAX_LEN);
    handleSyscallint(gethostname(host, MAX_LEN), "Getting hostname");
    char *user;
    user = getenv("USER");
    char *prompt = (char *)malloc(MAX_LEN);
    char *exitStr = (char *)malloc(MAX_LEN);
    exitStr[0] = '\0';
    if (exitCode == 0)
        sprintf(exitStr, COL_GRN ":')" COL_WHT);
    else if (exitCode == 1)
        sprintf(exitStr, COL_RED ":'(" COL_WHT);
    sprintf(prompt, "%s" COL_GRN "<%s@%s:" COL_BLU "%s" COL_GRN "> " COL_WHT, exitStr, user, host, cwd);

    free(cwd);
    free(host);
    free(exitStr);
    return prompt;
}