#include "minishell.h"

static char		*get_envstring(t_list_env *var)
{
	char *str;
	char *tmp;

	str = NULL;
	tmp = NULL;
	if (var)
	{
		str = ft_strjoin(tmp, var->name);
		if (str == NULL)
			return (NULL);
		if (var->has_equal == 1)
		{
			tmp = ft_strjoin(str, "=");
			if (str == NULL)
				return (NULL);
			free(str);
			str = NULL;
			if (var->content)
			{
				str = ft_strjoin(tmp, var->content);
				if (str == NULL)
					return (NULL);
				free(tmp);
				tmp = NULL;
			}
		}
	}
	return (str);
}


void			envlist_to_array(t_data *data)
{
	char **envp;
	t_list_env *tmp;
	int i;

	if (data->envp)
		free_2d_array(data->envp);
	i = envlstsize(data->envlist);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (envp == NULL)
		return ;
	tmp = data->envlist;
	i = -1;
	while (envp[++i])
	{
		envp[i] = get_envstring(tmp);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	data->envp = envp;
}

static void print_env(t_list_env *envs)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (tmp->has_equal == 1)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->content, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

void		shell_env(t_data *data)
{
	if (!data->ar->args[1])
	{
		print_env(data->envlist);
	}
	else
	{
		display_error("env", data->ar->args[1], "Too many arguments");
	}
}

