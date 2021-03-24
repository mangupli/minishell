#include "minishell.h"

void 	ft_exit(int errcode)
{
	exit(errcode);
}

/*
** Error codes:
**
** 1 - argument with executable
**
** 9 - Malloc failed
*/

void		display_error(char *commandname, char *errname, char *str)
{
	if (commandname)
	{
		ft_putstr_fd(commandname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errname)
	{
		ft_putstr_fd(errname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
		ft_putendl_fd(str, 2);
}
