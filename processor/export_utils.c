#include "minishell.h"

void	change_content(t_list_env **envs, t_list_env *new)
{
	t_list_env	*tmp;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			tmp->has_equal = new->has_equal;
			if (tmp->content)
			{
				if (ft_strcmp(tmp->content, new->content))
				{
					free(tmp->content);
					tmp->content = ft_strdup(new->content);
				}
			}
			else
				tmp->content = ft_strdup(new->content);
		}
		tmp = tmp->next;
	}
}

void	envsclear_node(t_list_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->content)
			free(env->content);
		free(env);
		env = NULL;
	}
}

void	add_content(t_list_env **envs, t_list_env *new)
{
	t_list_env	*tmp;
	char		*save;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			tmp->has_equal = new->has_equal;
			if (tmp->content)
			{
				save = tmp->content;
				tmp->content = ft_strjoin(save, new->content);
				free(save);
			}
			else
				tmp->content = ft_strdup(new->name);
		}
		tmp = tmp->next;
	}
}
