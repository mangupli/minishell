
#include "minishell.h"
#include "parseader.h"

char	**path_parser(t_list_env *envs)
{
	int i;

	i = 0;
	while (envs[i].name != NULL)
	{
		if (!ft_strcmp(envs[i].name, "PATH"))
			return (ft_split(envs[i].content, ':'));
		i++;
	}
	return (NULL);
}

/*
char	*find_path(char **paths, char *command)
{
	????
}*/
