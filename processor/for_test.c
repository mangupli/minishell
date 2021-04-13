#include "minishell.h"


int redir_type = 0;
/*
** Help to debug, type == 1 -> our function
*/

void print_arguments(char **args, char type)
{
	if (!type)
		printf("execve->");
	else
		printf("my_func->");
	printf("[%s]\n", args[0]);
	int z = 0;
	while(args[++z] != NULL)
		printf("args[%d]->[%s]\n", z, args[z]);
}

/*
** 1 = >
** 2 = >>
** 4 = <
*/

void which_redir(char **args)
{
	int i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], ">"))
			redir_type |= 1;
		if (!ft_strcmp(args[i], ">>"))
			redir_type |= 2;
		if (!ft_strcmp(args[i], "<"))
			redir_type |= 4;
	}
}

int find_redir(char **args)
{
	int i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], ">"))
			return (i);
		if (!ft_strcmp(args[i], ">>"))
			return (i);
		if (!ft_strcmp(args[i], "<"))
			return (i);
	}
	return (0);
}

void set_to_null_last_arguments(char **args, int start)
{
	while (args[start] != NULL)
	{
		ft_free((void **)(&args[start])); // doesnt work motherfucker
//		free(args[start]);
//		args[start] = NULL;
		start++;
	}
}

int	set_redir_fd(t_args *ar)
{
	int i;

	i = -1;
	while (ar->args[++i])
	{
		if (!ft_strcmp(ar->args[i], "<"))
		{
			if (ar->file[1] >= 0)
				close(ar->file[1]);
			ar->file[1] = open(ar->args[i + 1], O_RDONLY);
			if (ar->file[1] < 0)
			{
				display_error("minishell", ar->args[i + 1],
							  "No such file or directory");
				g_status = 1;
				return (-1);
			}
		}
		else if (!ft_strcmp(ar->args[i], ">>"))
		{
			if (ar->file[0] >= 0)
				close(ar->file[0]);
			ar->file[0] = open(ar->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
			if (ar->file[0] < 0)
			{
				display_error("minishell", ar->args[i + 1],
							  strerror(errno));
				g_status = 1;
				return (-1);
			}
		}
		else if (!ft_strcmp(ar->args[i], ">"))
		{
			if (ar->file[0] >= 0)
				close(ar->file[0]);
			ar->file[0] = open(ar->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0744);
			if (ar->file[0] < 0)
			{
				display_error("minishell", ar->args[i + 1],
				  strerror(errno));
				g_status = 1;
				return (-1);
			}
		}
	}
	return (0);
}

int	set_redir(t_data *data, t_args **args)
{
	t_args *tmp;
	int ret;
	int start_redir;

	tmp = *args;
	while (tmp)
	{
		start_redir = find_redir(tmp->args);
		if (start_redir)
		{
			ret = set_redir_fd(tmp);
			if (ret == -1)
				return (-1);
			free_2d_array(tmp->args, start_redir);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
** Creates the list of type t_args.
** Arguments :
** (1)string to the end of the line or to the ';'
** (2)the pointer to the lode that should be added
** (3)number of '|' in the string
**
** How to add node on the list:
** We need two pointers (args *) - one for the head, one for the node ->
** t_args *head = NULL; -> first, set head to NULL
** t_args *node = arglstnew(char **args, char type); -> this creates new node
** args_lstadd_back(&head, node); -> adds node to the end of the head list
*/

int get_args_list(char *str, t_data *data, int pipes)
{
	int i;
	char *newstr;
	char **args;
	int start;
	t_args *node;
	int j;
	int ret;

	data->ar = NULL;

	i = -1;
	j = 0;
	start = 0;
	while (str[++i] && j <= pipes)
	{
		if (str[i] == '|')
		{
			newstr = ft_substr(str, start, i - start);
			args = ft_split(newstr, ' ');
			node = arglstnew(args, '|');
			args_lstadd_back(&data->ar, node);
			start = i + 1;
			j++;

			ft_free((void **)&newstr);
		}
	}

	newstr = ft_substr(str, start, ft_strlen(str) - start);
	args = ft_split(newstr, ' ');
	node = arglstnew(args, 0);
	args_lstadd_back(&data->ar, node);
	ft_free((void **)&newstr);

	ret = set_redir(data, &data->ar);
	if (ret)
		return (-1);

	return (0);
}

void change_dollar(t_data *data, char **arg)
{
	char *env;
	char *content;


	env = ft_substr(*arg, 1, ft_strlen(*arg) - 1);
	ft_free((void **)&(*arg));
	if (!ft_strcmp(env, "?"))
	{
		content = ft_itoa(g_status);
		*arg = content;
	}
	else
	{
		content = find_env_content(data->envlist, env);
		if (content)
			*arg = ft_strdup(content);
		else
			*arg = ft_strdup("");
	}
	if (env)
		ft_free((void **)&env);
}

void dollar(t_data *data)
{
	t_args *tmp;
	int i;

	tmp = data->ar;
	while (tmp)
	{
		if (tmp->args && tmp->args[0])
		{
			i = 0;
			while (tmp->args[++i])
			{
				if (tmp->args[i][0] == '$')
				{
					change_dollar(data, &tmp->args[i]);
				}
			}
		}
		tmp = tmp->next;
	}
}

int test_parser(char *line, int count, t_data *data)
{
	int ret;
	int i;
	int end;
	char *str;
	int status;

	ret = 0;
	i = -1;
	end = 0;
	while (line[++i])
	{
		if (line[i] == ';')
		{
			if (line[i + 1] == ';')
			{
				display_error("minishell", "syntax error", "unexpected token");
				return (-1);
			}
			else
			{
				ret = i + 1;
				end = ret - 1;
				break;
			}
		}
	}
	if (ret == 0)
	{
		ret = i;
		end = ret;
	}
	str = ft_substr(line, 0, end);
	i = -1;
	count = 0;
	while (++i < end)
	{
		if (line[i] == '|')
			count++;
	}

	status = get_args_list(str, data, count);
	free(str);
	if (status)
		return (-1);
	dollar(data);
	return (ret);
}
