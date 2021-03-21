#include "minishell.h"

void 		display_error(char *errname, char *str, int nline)
{
	ft_putstr_fd("superbash: ", 2);
	if (errname)
	{
		ft_putstr_fd(errname, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
		ft_putstr_fd(str, 2);
	if (nline)
		write(1, "\n", 2);
}