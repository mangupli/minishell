#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<unistd.h>
# include	<unistd.h>
# include	<term.h>
# include	<string.h>
# include	<curses.h>
# include	<errno.h>
# include	<sys/ioctl.h>
# include	<readline.h>
# include	"../libft/includes/libft.h"

/*
 * Logic functions
 */

void 		display_error(char *ername, char *str, int nline);
int			execution(char *filename, char **env);
int			shell_echo(char **args);

/*
 * Parser functions
 */

t_list		*parse_env(char **env);

#endif