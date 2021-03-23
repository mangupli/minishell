#include "minishell.h"

int shell_pwd(t_data *data)
{
	char *pwd;

	(void)data;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		display_error(NULL, "Malloc allocation failed\n");
		ft_exit(9);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}