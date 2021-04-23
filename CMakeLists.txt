cmake_minimum_required(VERSION 3.17)
project(shell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -ltermcap)
include_directories(shell includes libft)

add_executable(shell main.c

        includes/minishell.h
        includes/parseader.h


        processor/readline.c
        processor/terminal_management.c
        processor/append_line.c
        processor/history.c
        processor/exit.c
        processor/execution.c
        processor/echo.c
        processor/pwd.c
        processor/cd.c
        processor/proc_utils.c
        processor/export.c
        processor/env.c
        processor/envir_var.c
        processor/unset.c
        processor/find_fd.c
        processor/signals.c
        processor/envslist_utils.c
        processor/argslist_utils.c
        parser/path_parser.c
        processor/for_test.c

        parser/begin.c
        parser/helpers.c
        parser/quotes.c
        parser/locations.c
        parser/strings.c
        parser/validators.c
        parser/splitters.c
        parser/spaces.c
        parser/utils.c
        parser/args.c
        parser/envs.c)

target_link_libraries(shell /Users/mspyke/projects/minishell/shell/libft/libft.a)