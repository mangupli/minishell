#include "minishell.h"

static void	new_pwd_env(t_list_env *envs, char *new_pwd)
{
	t_list_env	*pwd;
	t_list_env	*oldpwd;

	pwd = find_env_pointer(envs, "PWD");
	oldpwd = find_env_pointer(envs, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->content);
		oldpwd->content = NULL;
		oldpwd->content = pwd->content;
	}
	pwd->content = new_pwd;
}

int	change_dir(char *arg)
{
	int	ret;

	ret = chdir(arg);
	if (ret == -1)
	{
		g_struct.status = 1;
		display_error("cd", arg, "No such file or directory");
		return (-1);
	}
	return (0);
}

void	shell_cd(t_data *data, char **args)
{
	char	*new_pwd;
	char	*home;
	int		ret;

	ret = ft_strcmp(args[1], "~") && ft_strcmp(args[1], "--");
	if (!args[1] || !ret)
	{
		home = find_env_content(data->envlist, "HOME");
		ret = change_dir(home);
		if (ret == -1)
			return ;
	}
	else
	{
		ret = change_dir(args[1]);
		if (ret == -1)
			return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		new_pwd_env(data->envlist, new_pwd);
	else
		display_error("cd", NULL, strerror(errno));
	g_struct.status = 0;
}
