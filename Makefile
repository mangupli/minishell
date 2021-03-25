# Compilation #

FLAGS = -Wall -Wextra -Werror

# Directories #

PARSER_DIR = ./parser/
PROCESS_DIR = ./processor/
OBJS_DIR = ./objs/

INC_DIR = ./includes/

PROCESS_INC = $(INC_DIR)minishell.h
PARSER_INC = $(INC_DIR)parseader.h
LINK_INC = -I $(INC_DIR)

# Source files #

NAME = bash

SRCS_MAIN = main.c

SRCS_PROCCESS = readline.c terminal_management.c append_line.c \
history.c exit.c execution.c echo.c pwd.c cd.c utils.c export.c \
env.c envir_var.c listjob.c

SRCS_PARSER = env_parser.c env_parser2.c path_parser.c validators.c

# Object files #

OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_PROCCESS = $(SRCS_PROCCESS:.c=.o)
OBJS_PARSER = $(SRCS_PARSER:.c=.o)
OBJS_DIR = ./objs/
OBJS = $(addprefix  $(OBJS_DIR), $(OBJS_PROCCESS) $(OBJS_PARSER) $(OBJS_MAIN))

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) libft/libft.a -ltermcap -o $@

$(OBJS_DIR)%.o : $(PROCESS_DIR)%.c $(PROCESS_INC)
	@mkdir -p $(OBJS_DIR)
	gcc -I./includes -c $< -o $@

$(OBJS_DIR)%.o : %.c
	gcc -I./includes -c $< -o $@

$(OBJS_DIR)%.o : $(PARSER_DIR)%.c $(PARSER_INC)
	gcc -I./includes -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
