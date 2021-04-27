#include "minishell.h"

t_list_env *find_env_pointer(t_list_env *envs, char *name)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void set_shlvl(char **env, t_list_env **new_list)
{
	int			lvl;
	char		*content;
	int			num;
	t_list_env *new_elem;

	content = find_env_content(*new_list, "SHLVL");
	if (content)
	{
		num = ft_atoi(content);
		lvl = num + 1;
		content = ft_itoa(lvl);
		new_elem = envlistnew1("SHLVL", content, 1);
		change_content(new_list, new_elem);
		free(content);
	}
	else
		add_var_to_list(new_list, "SHLVL=1");
}



t_list_env	*get_envlist(char **env)
{
	int i;
	t_list_env *new_list;
	t_list_env *new_elem;

	i = -1;
	new_list = NULL;
	while (env[++i])
	{
		new_elem = envlstnew(env[i]);
		env_lst_addback(&new_list, new_elem);
	}
	i = find_envvar(&new_list, "OLDPWD");
	if (!i)
		add_var_to_list(&new_list, "OLDPWD=");
	/*
	i = find_envvar(&new_list, "PWD");
	if (!i)
	{
		new_elem = envlistnew1("PWD", getcwd(NULL, 0), 1);
		env_lst_addback(&new_list, new_elem);
	}
	i = find_envvar(&new_list, "SHLVL");
	if (!i)
		add_var_to_list(&new_list, "SHLVL=1");
	else
		set_shlvl(env, &new_list);
	 */
	return (new_list);
}

int	find_envvar(t_list_env **envs, char *name)
{
	t_list_env *tmp;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char		*find_env_content(t_list_env *envs, char *name)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
