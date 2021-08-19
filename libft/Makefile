# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspyke <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 20:18:10 by mspyke            #+#    #+#              #
#    Updated: 2020/12/29 18:58:43 by mspyke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation #

FLAGS = -Wall -Wextra -Werror

# Directories #

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/
GNL_DIR = ./gnl/

INC_DIR = ./includes/
INC_LIBFT = $(INC_DIR)libft.h
INC_GNL = $(INC_DIR)get_next_line.h
LINK_INC = -I $(INC_DIR)

# Source files #

NAME = libft.a

SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c ft_itoa.c ft_numlen.c\
		\
		ft_memccpy.c  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_realloc.c\
		\
		ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c ft_putendl_fd.c \
        ft_putnbr.c ft_putnbr_fd.c ft_putunbr.c \
        \
        ft_split.c ft_str_to_upper.c ft_str_to_lower.c ft_strcmp.c ft_strncpy.c ft_strndup.c ft_strnew.c \
        ft_strnlen.c ft_strchr.c ft_strjoin.c ft_strlcpy.c ft_strclr.c ft_strlcat.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strtrim.c ft_strmapi.c ft_strrev.c \
		\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strdup.c ft_str_is_numeric.c \
		\
		ft_strcmp.c ft_strcpy.c  ft_strlen.c 

SRCS_GNL = get_next_line.c get_next_line_utils.c

# Object files #

OBJS_LIBFT = ${SRCS:.c=.o}
OBJS_GNL = ${SRCS_GNL:.c=.o}
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIBFT) $(OBJS_GNL))

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $(OBJS)
	ranlib $@
	@echo "\033[32m$@ successfully created\033[0m" ✅

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INC_LIBFT)
	@mkdir -p $(OBJS_DIR)
	gcc $(FLAGS) $(LINK_INC) -c $< -o $@

$(OBJS_DIR)%.o: $(GNL_DIR)%.c $(INC_GNL)
	gcc $(FLAGS) $(LINK_INC) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
