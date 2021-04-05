cmake_minimum_required(VERSION 3.17)
project(shell C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS -ltermcap)

include_directories( ./includes)
include_directories( ./libft/includes)

link_directories(libft)

add_executable(shell

        main.c

        includes/minishell.h
        includes/parseader.h
        libft/includes/libft.h

        processor/readline.c
        processor/terminal_management.c
        processor/append_line.c
        processor/history.c
        processor/exit.c
        processor/execution.c
        processor/echo.c
        processor/pwd.c
        processor/cd.c
        processor/utils.c
        processor/export.c
        processor/env.c
        processor/envir_var.c
        processor/envslist_utils.c
        processor/unset.c
        processor/find_fd.c
        processor/argslist_utils.c

        processor/for_test.c


        parser/env_parser.c
        parser/env_parser2.c
        parser/line_parser.c
        parser/line_parser2.c
        parser/path_parser.c
        parser/validators.c)

target_link_libraries(shell /Users/mspyke/projects/minishell/shell/libft/libft.a)
