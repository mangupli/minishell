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
	char **dst;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
		{
			dst = ft_split(tmp->content, ':');
			return (dst);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int try_fd(char *full_path, t_args *ar)
{
	int fd;

	fd = open(full_path, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		free(ar->args[0]);
		ar->args[0] = ft_strdup(full_path);
		if (ar->args[0] == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

static int try_path(char **paths, t_args *ar)
{
	int i;
	char *full_path;
	char *buf;
	int ret;

	i = -1;
	while (paths[++i])
	{
		buf = ft_strjoin(paths[i], "/");
		if (buf == NULL)
			return (-1);
		full_path = ft_strjoin(buf, ar->args[0]);
		if (full_path == NULL)
			return (-1);
		ret = try_fd(full_path, ar);
		free(buf);
		free(full_path);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int find_function_path(t_args *ar, t_list_env *envs)
{
	char **paths;
	int ret;

	paths = path_parser(envs);
	if (paths)
	{
		ret = try_path(paths, ar);
		free_2d_array(paths);
		if (ret == -1)
			return (ret);
	}
	else
		return (-1);
	return (0);
}
