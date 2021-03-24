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
        processor/utils.c
        processor/export.c
        processor/env.c
        parser/env_parser.c
        parser/env_parser2.c
        parser/path_parser.c)

target_link_libraries(shell /Users/mspyke/projects/minishell/shell/libft/libft.a)



