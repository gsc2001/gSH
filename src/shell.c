#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "mpwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "sysCommand.h"
#include "pinfo.h"
#include "errorHandler.h"
#include "signalHandlers.h"
#include "history.h"
#include "jobs.h"
#include "fg.h"
#include "bg.h"
#include "env.h"
#include "kjob.h"
#include "piping.h"

void init()
{
    HOME = handleSyscallchar(getcwd(NULL, MAX_LEN - 1), "Getting home dir");

    // load history
    loadHistory();

    // signal handlers
    signal(SIGCHLD, sigchldHandler);
    // signal(SIGINT, sigintHandler);
    signal(SIGTSTP, sigtstpHandler);
}
const int builtInN = 12;

const char *builtInComs[] = {
    "pwd",
    "cd",
    "ls",
    "pinfo",
    "echo",
    "history",
    "jobs",
    "fg",
    "bg",
    "setenv",
    "unsetenv",
    "kjob",
};

// built in command functions
void (*builtInComExec[])(Command c) = {
    pwdExec,
    cdExec,
    lsExec,
    pinfoExec,
    echo,
    historyExec,
    jobsExec,
    fgExec,
    bgExec,
    setenvExec,
    unsetenvExec,
    kjobExec,
};

void execCommand(Command c)
{
    int commandIndex = -1;

    for (int i = 0; i < builtInN; i++)
    {
        if (!strcmp(c.cmd, builtInComs[i]))
        {
            commandIndex = i;
            break;
        }
    }

    if (commandIndex != -1)
        builtInComExec[commandIndex](c);
    else
    {
        execSys(c);
    }
}

void repl()
{
    size_t inpsize;
    char *inp = 0;
    size_t bufsize = 0;

    while (1)
    {
        char *prompt = get_prompt();
        printf("%s", prompt);
        fflush(stdout);
        inpsize = getline(&inp, &bufsize, stdin);
        if (inpsize < 0)
            break;
        inp[strlen(inp) - 1] = '\0';

        // add to history
        addToHistory(inp);

        char *inpCopy = (char *)malloc(strlen(inp) + 1);
        inpCopy[0] = '\0';
        strcpy(inpCopy, inp);

        // parse inp
        ParsedCommands parsed = parse(inpCopy);

        if (DEBUG)
        {
            fprintf(stderr, "\n\n=================DEBUG==============\n\n");
            fprintf(stderr, "nPipes=%d\n", parsed.n);
            for (int i = 0; i < parsed.n; i++)
            {
                PipedCommands piped = parsed.piped[i];
                fprintf(stderr, "pipedN=%d\n", piped.n);
                for (int j = 0; j < piped.n; j++)
                {
                    Command com = piped.commands[j];
                    fprintf(stderr, "cmd=%s, argc=%d, backround=%d\n", com.cmd, com.argc, com.bg);
                    fprintf(stderr, "args->");
                    for (int k = 0; k < com.argc; k++)
                        fprintf(stderr, "%s,", com.args[k]);
                    fprintf(stderr, "\n");
                }
            }
            fprintf(stderr, "\n\n==============END====================\n\n");
        }

        for (int i = 0; i < parsed.n; i++)
            execPiped(parsed.piped[i]);

        //cleanup
        free(prompt);
        free(inpCopy);
    }
}

void byebye()
{
    saveHistory();
}
