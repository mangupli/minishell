#include "minishell.h"

/*
** Help to debug, type == 1 -> our function
*/

void print_arguments(char **args, char type)
{
	int z = 0;
	printf("execve->[%s]\n", args[0]);
	while(args[++z])
		printf("args[%d]->[%s]\n", z, args[z]);
	//end debug
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

int get_args_list(char *str, t_data *data, int count)
{
	int i;
	char *newstr;
	char **args;
	int start;
	t_args *node;
	int j;

	data->ar = NULL;

	i = -1;
	j = 0;
	start = 0;
	while (str[++i] && j <= count)
	{
		if (str[i] == '|')
		{
			newstr = ft_substr(str, start, i - start);
			args = ft_split(newstr, ' ');
			node = arglstnew(args, '|');
			args_lstadd_back(&data->ar, node);
			start = i + 1;
			j++;

			free(newstr);
			newstr = NULL;
		}
	}

	newstr = ft_substr(str, start, ft_strlen(str) - start);
	args = ft_split(newstr, ' ');
	node = arglstnew(args, 0);
	node->type = 0;
	args_lstadd_back(&data->ar, node);
	free(newstr);
	newstr = NULL;

	printf("argslist size %d\n", argslstsize(data->ar));

	return (0);
}

void change_dollar(t_data *data, char **arg)
{
	char *env;
	char *content;


	env = ft_substr(*arg, 1, ft_strlen(*arg) - 1);
	ft_free(*arg);
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
		ft_free(env);
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

	get_args_list(str, data, count);
	free(str);
	dollar(data);


	return (ret);
}
