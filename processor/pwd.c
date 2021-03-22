#include "minishell.h"

int shell_pwd(char **args)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		error_and_exit(NULL, "Malloc allocation failed\n", 1, 9);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}