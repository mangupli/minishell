#include "minishell.h"

t_list		*parse_env(char **env)
{
	int i;
	t_list *env_list;
	t_list *new;

	i = -1;
	env_list = NULL;
	while (env[++i])
	{
		new = ft_lstnew(env[i]);
		ft_lstadd_back(&env_list, new);
	}
	return (env_list);
}