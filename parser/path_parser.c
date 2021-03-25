
#include "minishell.h"
#include "parseader.h"

char	**path_parser(t_list_env *envs)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return (ft_split(tmp->content, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
/*
char	*find_path(char **paths, char *command)
{

}
*/

void find_function_path(char *func, t_list_env *envs, t_data *data)
{
	char **paths;
	int i;
	int fd;
	char *full_path;

	paths = path_parser(envs);
	i = -1;
	while(paths[++i])
	{
		full_path = ft_strjoin(paths[i], func);
		fd = open(full_path, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			free(data->args[0]);
			data->args[0] = ft_strdup(full_path);
		}
	}

}
