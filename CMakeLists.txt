cmake_minimum_required(VERSION 3.17)
project(shell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -ltermcap)
include_directories(shell includes libft)

add_executable(shell main.c
        includes/minishell.h
        readline.c
        terminal_management.c
        append_line.c
        history.c
        exit.c
        env_variables.c
        execution.c
        echo.c)

target_link_libraries(shell /Users/mspyke/projects/minishell/shell/libft/libft.a)



