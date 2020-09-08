#include "parse.h"
#include "utils.h"

Command parseCommand(char *command_raw)
{
    char *command_ = (char *)malloc(strlen(command_raw) + 1);
    command_[0] = '\0';
    strcpy(command_, command_raw);

    Command command;
    command.args = NULL;
    command.flags = NULL;
    command.command_str = (char *)malloc(strlen(command_) + 1);
    command.bg = 0;

    strcpy(command.command_str, command_);
    command.cmd = strtok(command_, " ");
    if (command.cmd == NULL)
    {
        command.cmd = NULL;
        command.command_str = NULL;
        return command;
    }

    command.argc = 0;

    char *args_[MAX_LEN];
    char *flags = (char *)malloc(MAX_LEN);
    flags[0] = '\0';
    char *arg;
    arg = strtok(NULL, " ");

    // loop over args
    while (arg)
    {
        if (!strlen(arg))
            continue;

        if (arg[0] == '-')
            strcat(flags, arg + 1);
        else
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
    if (strlen(flags))
    {
        command.flags = (char *)malloc(strlen(flags) + 1);
        strcpy(command.flags, flags);
    }
    free(flags);
    return command;
}

ParsedCommands parse(char *inp)
{
    replaceTabs(inp);
    char *commands[MAX_LEN];
    int nCommands = 0;
    char *token = strtok(inp, ";");
    while (token)
    {
        commands[nCommands++] = token;
        token = strtok(NULL, ";");
    }

    ParsedCommands parsed;
    parsed.n = nCommands;
    parsed.commands = (Command *)malloc(nCommands * sizeof(Command));
    for (int i = 0; i < nCommands; i++)
    {
        if (!strlen(commands[i]))
            continue;
        parsed.commands[i] = parseCommand(commands[i]);
    }
    return parsed;
}