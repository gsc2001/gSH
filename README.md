# gSH

A basic C shell

## Project Structure

The project contains the following folder with files described:

-   **build**: stores the build files
-   **include**: stores all header files
-   **src**: stores `.c` source code files

## Instructions

-   ### Building

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
-   `parse.c`: File with functions to take raw input string and parse it. Stores `;` seperated commands in `Command` struct and collection of all commands in input string in `ParsedCommands` struct
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
-   `signalHandlers.c`: File with signal handlers. For now handler only for `SIGCHLD` signal
-   `utils.c`: File with some utility functions
