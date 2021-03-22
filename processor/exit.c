#include "minishell.h"

/*
** Error codes:
**
** 1 - argument with executable
**
** 9 - Malloc failed
*/


void		error_and_exit(char *errname, char *str, int nline, int errcode)
{
	ft_putstr_fd("superbash: ", 2);
	if (errname)
	{
		ft_putstr_fd(errname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
		ft_putendl_fd(str, 2);
	exit(errcode);
}