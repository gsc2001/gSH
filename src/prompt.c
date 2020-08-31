#include "globals.h"
#include "prompt.h"
#include "utils.h"
#include "errorHandler.h"

char *get_prompt()
{
    char *cwd = (char *)malloc(MAX_LEN);
    handleSyscallchar(getcwd(cwd, MAX_LEN), "Getting CWD");
    cwd = replaceHomeDir(cwd);
    char *host = (char *)malloc(MAX_LEN);
    handleSyscallint(gethostname(host, MAX_LEN), "Getting hostname");
    char *user = (char *)malloc(MAX_LEN);
    user = getenv("USER");

    char *prompt = (char *)malloc(MAX_LEN);
    sprintf(prompt, "<%s@%s:%s> ", user, host, cwd);
    return prompt;
}