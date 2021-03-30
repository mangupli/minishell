#include "minishell.h"
#include "parseader.h"

void new_pwd_env(t_list_env *envs, char *new_pwd)
{
	t_list_env *pwd;
	t_list_env *oldpwd;

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


/*
** Is there always OLDPWD and what if it goes unset?
*/

void 	shell_cd(t_data *data)
{
	char *new_pwd;
	char *home;
	int ret;

	if (!data->ar->args[1] || !ft_strcmp(data->ar->args[1], "~") ||
		!ft_strcmp(data->ar->args[1], "--"))
	{
		home = find_env_content(data->envlist, "HOME");
		ret = chdir(home); // try with Null
		if (ret == -1)
			display_error("cd", NULL, "HOME not set");
	}
	else
	{
		ret = chdir(data->ar->args[1]);
		if (ret == -1)
			display_error("cd", data->ar->args[1], "No such file or directory");
	}
	new_pwd = getcwd(NULL, 0);
	new_pwd_env(data->envlist, new_pwd);
}
