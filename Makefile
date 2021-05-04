# Compilation #

FLAGS = -Wall -Wextra -Werror

# Directories #

PARSER_DIR = ./parser/
PROCESS_DIR = ./processor/
OBJS_DIR = ./objs/

LIBFT_DIR := ./libft/

INC_DIR = ./includes/

PROCESS_INC = $(INC_DIR)minishell.h
PARSER_INC = $(INC_DIR)parseader.h
LINK_INC = -I $(INC_DIR)

# Source files #

NAME = minishell

SRCS_MAIN = main.c
LIBFT = libft.a

SRCS_PROCCESS = readline.c get_cols.c append_line.c \
history.c exit.c execution.c echo.c pwd.c cd.c proc_utils.c export.c \
env.c envir_var.c envslist_utils.c unset.c find_fd.c argslist_utils.c \
signals.c reset.c buildin.c export_utils.c echo_n.c\


SRCS_PARSER = path_parser.c args.c begin.c envs.c helpers.c locations.c \
quotes.c spaces.c splitters.c strings.c utils.c validators.c redirectors.c



# Object files #

OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_PROCCESS = $(SRCS_PROCCESS:.c=.o)
OBJS_PARSER = $(SRCS_PARSER:.c=.o)
OBJS_DIR = ./objs/
OBJS = $(addprefix  $(OBJS_DIR), $(OBJS_PROCCESS) $(OBJS_PARSER) $(OBJS_MAIN))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) $(FLAGS) libft/libft.a -ltermcap -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)%.o : $(PROCESS_DIR)%.c $(PROCESS_INC)
	@mkdir -p $(OBJS_DIR)
	gcc $(FLAGS) -I./includes -c $< -o $@

$(OBJS_DIR)%.o : %.c
	gcc $(FLAGS) -I./includes -c $< -o $@

$(OBJS_DIR)%.o : $(PARSER_DIR)%.c $(PARSER_INC)
	gcc -I./includes -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
