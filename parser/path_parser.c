#include "minishell.h"
#include "parseader.h"

int		get_curr_location(t_args *ar, t_list_env *envs)
{
	char *buf;
	char *pwd;
	char *full_path;
	int fd;

	buf = ft_substr(ar->args[0], 1, ft_strlen(ar->args[0]) - 1);
	pwd = find_env_content(envs, "PWD");
	if (pwd)
	{
		full_path = ft_strjoin(pwd, buf);
		fd = open(full_path, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			free(ar->args[0]);
			ar->args[0] = ft_strdup(full_path);
			free(full_path);
			free(buf);
			return (1);
		}
		free(buf);
	}
	return (0);
}

char	**path_parser(t_list_env *envs)
{
	t_list_env *tmp;
	char **ret;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
		{
			ret = ft_split(tmp->content, ':');
			return (ret);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int find_function_path(t_args *ar, t_list_env *envs)
{
	char **paths;
	int i;
	int fd;
	char *full_path;
	char *buf;

	paths = path_parser(envs);
	if (paths)
	{
		i = -1;
		while (paths[++i])
		{
			buf = ft_strjoin(paths[i], "/");
			full_path = ft_strjoin(buf, ar->args[0]);
			fd = open(full_path, O_RDONLY);
			if (fd > 0)
			{
				close(fd);
				free(ar->args[0]);
				ar->args[0] = ft_strdup(full_path);
				free(full_path);
				free(buf);
				free_2d_array(paths);
				return (1);
			}
			free(buf);
			free(full_path);
		}
		free_2d_array(paths);
	}
	return (0);
}
