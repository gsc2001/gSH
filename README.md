# gSH

A basic C shell

## Project Structure

The project contains the following folder with files described:

-   **build**: stores the build files
-   **include**: stores all header files
-   **src**: stores `.c` source code files

## Instructions

-   ### Building

    Make sure you have a build folder in the current directory. If not then create by

    ```bash
    mkdir build
    ```

    To build normally

    ```bash
    make
    ```

    To build with debugging on

    ```
    make debug
    ```

    ```
    NOTE: All the build files will be in the build folder
    ```

-   ### Running

    ```bash
    ./gSH
    ```

-   ### Cleanup

    ```bash
    make clean
    ```

## File Contents

-   `globals.h`: File with global variable, structs and header files declarations.

The following files are in `src` directory. The corresponding `.h` files can be found in `include` directory. `.h` files also contain brief description.

-   `main.c`: File with `main()` .Calls init ,repl and destroy functions. (This file does not has a corresponding `.h` file)
-   `parse.c`: File with functions to take raw input string and parse it.First seperates at `";"` for `PipedCommands` struct then seperates at `"|"` to extract `Command` and returns a struct `ParsedCommands` with all neccessary things.
-   `shell.c`: File with init, repl, byebye function. This also has function to execute `ParsedCommands` using corresponding executor
-   `prompt.c`: File with function to return prompt string.
-   `cd.c`: File with cd command implementation and executor
-   `echo.c`: File with echo command implementation and executor
-   `ls.c`: File with ls command implementation and executor
-   `mpwd.c`: File with pwd command implementation and executor
-   `pinfo.c`: File with pinfo command implementation and executor
-   `errorHandler.c`: File with error handlers for syscalls
-   `history.c`: File with history command implementation and executor. This file also contains functions to add a command to history, save history and load history
-   `sysCommand.c`: File with function for execution of non-builtin commands in foreground or background
-   `signalHandlers.c`: File with signal handlers.
-   `utils.c`: File with some utility functions
-   `bg.c`: File with bg functionality
-   `env.c`: File with some setenv and unsetenv option
-   `fg.c`: File with fg command implementation and executor
-   `jobs.c`: File with jobs command implementation and executor
-   `kjob.c`: File with kjob command implementation and executor
-   `overkill.c`: File with overkill command implementation and executor
-   `piping.c`: File with funciton to execute piped commands in `PipedCommands` struct by making pipes between consecutive processes.
-   `processList.c`: File with functions to handle background process linked list.
-   `redirecting.c`: File with 2 functions 1st to start I/O redirection and 2nd to restore all STDIN and STDOUT.
