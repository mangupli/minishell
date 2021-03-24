#include "minishell.h"
#include "parseader.h"

void new_pwd_env(t_env *envs, char *new_pwd)
{
	t_env *pwd;
	t_env *oldpwd;
	int i;

	pwd = find_env_pointer(envs, "PWD");
	oldpwd = find_env_pointer(envs, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->content);
		oldpwd->content = NULL;
		oldpwd->content = pwd->content;
	}
	else
	{
		//create new elemenent OLDPWD ?
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

	if (!data->args[1] || !ft_strcmp(data->args[1], "~") ||
		!ft_strcmp(data->args[1], "--"))
	{
		home = find_env_content(data->env, "HOME");
		ret = chdir(home);
		if (ret == -1)
			display_error("cd", NULL, "HOME not set");
	}
	else
	{
		ret = chdir(data->args[1]);
		if (ret == -1)
			display_error("cd", data->args[1], "No such file or directory");
	}
	new_pwd = getcwd(NULL, 0);
	new_pwd_env(data->env, new_pwd);
}
