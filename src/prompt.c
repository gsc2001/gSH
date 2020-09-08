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
    sprintf(prompt, "<%s@%s:%s> ", user, host, cwd);

    free(cwd);
    free(host);
    return prompt;
}