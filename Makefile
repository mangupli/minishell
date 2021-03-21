NAME = bash

SRCS = main.c readline.c terminal_management.c append_line.c \
history.c exit.c env_variables.c execution.c echo.c

PARSER_FILES = env_parser.c
SRCS_PARSER = $(addprefix  $(PARSERDIR), $(PARSER_FILES))
PARSER_DIR = parser/


HEADER = includes/minishell.h includes/parseader.h

OBJ_FILES = $(SRCS:.c=.o)
OBJ_PARSER = $(SRCS_PARSER:.c=.o)
OBJS_DIR = ./objs/
OBJS = $(addprefix  $(OBJS_DIR), $(OBJ_FILES) $(OBJ_PARSER))

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) libft/libft.a -ltermcap -o $@

$(OBJS_DIR)%.o : %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	gcc -I./includes -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
