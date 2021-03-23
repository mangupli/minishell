#include "minishell.h"
#include "parseader.h"

char		*find_env_content(t_env *envs, char *name)
{
	int i;

	i = 0;
	while (envs[i].name != NULL && envs[i].content != NULL)
	{
		if (!ft_strcmp(envs[i].name, name))
			return (envs[i].content);
		i++;
	}
	return (NULL);
}

t_env *find_env_pointer(t_env *envs, char *name)
{
	int i;

	i = 0;
	while (envs[i].name != NULL && envs[i].content != NULL)
	{
		if (!ft_strcmp(envs[i].name, name))
			return (&envs[i]);
		i++;
	}
	return (NULL);
}

