#include "parse.h"
#include "utils.h"

Command parseCommand(char *command_raw)
{
    char *command_ = (char *)malloc(strlen(command_raw) + 1);
    command_[0] = '\0';
    strcpy(command_, command_raw);

    Command command;
    command.args = NULL;
    command.bg = 0;
    command.cmd = strtok(command_, " ");
    if (command.cmd == NULL)
        return command;

    command.argc = 0;
    char *args_[MAX_LEN];
    char *arg;
    arg = strtok(NULL, " ");

    // loop over args
    while (arg)
    {
        if (!strlen(arg))
            continue;

        args_[command.argc++] = arg;
        arg = strtok(NULL, " ");
    }
    if (command.argc > 0 && !strcmp(args_[command.argc - 1], "&"))
    {
        command.argc--;
        command.bg = 1;
    }
    command.args = (char **)malloc(command.argc * sizeof(char *));
    for (int i = 0; i < command.argc; i++)
        command.args[i] = args_[i];
    return command;
}

PipedCommands parsePiped(char *pipedCommand)
{
    char **commands = (char **)malloc(MAX_LEN * sizeof(char *));
    int nCommands = splitString(commands, pipedCommand, "|");
    PipedCommands piped;
    piped.n = nCommands;
    piped.commands = (Command *)malloc(nCommands * sizeof(Command));
    for (int i = 0; i < nCommands; i++)
    {
        if (!strlen(commands[i]))
            continue;
        piped.commands[i] = parseCommand(commands[i]);
        free(commands[i]);
    }

    return piped;
}

ParsedCommands parse(char *inp)
{
    replaceTabs(inp);
    char **pipedCommands = (char **)malloc(MAX_LEN * sizeof(char *));
    int nPiped = splitString(pipedCommands, inp, ";");
    ParsedCommands parsed;
    parsed.n = nPiped;
    parsed.piped = (PipedCommands *)malloc(nPiped * sizeof(PipedCommands));
    for (int i = 0; i < nPiped; i++)
    {
        if (!strlen(pipedCommands[i]))
            continue;
        parsed.piped[i] = parsePiped(pipedCommands[i]);
        free(pipedCommands[i]);
    }
    return parsed;
}