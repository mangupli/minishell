
#include "../includes/parseader.h"
#include "../includes/minishell.h"

char	**path_parser(t_env *envs)
{
	int i;

	i = 0;
	while (envs[i].name != NULL)
	{
		if (strnstr(envs[i].name, "PATH", 5))
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
