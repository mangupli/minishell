#include "minishell.h"

int		test_mylstsize(t_args *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_args *test_mylstnew(char **args)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));
	if (NULL == new)
		return (NULL);
	new->args = args;
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_args	*test_mylstlast(t_args *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	test_mylstadd_back(t_args **lst, t_args *new)
{
	t_args	*tmp;

	if (lst)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
			test_mylstlast(tmp)->next = new;
	}
}

int get_args_list(char *str, t_data *data, int count)
{
	int i;
	char *newstr;
	char **args;
	int start;
	t_args *root;
	t_args *node;
	int j;

	root = NULL;

	i = -1;
	j = 0;
	start = 0;
	while (str[++i] && j <= count)
	{
		if (str[i] == '|')
		{
			newstr = ft_substr(str, start, i - start);
			args = ft_split(newstr, ' ');
			node = test_mylstnew(args);
			node->type = '|';
			test_mylstadd_back(&root, node);
			start = i + 1;
			j++;
		}
	}

	newstr = ft_substr(str, start, ft_strlen(str) - start);
	args = ft_split(newstr, ' ');
	node = test_mylstnew(args);
	node->type = 0;
	test_mylstadd_back(&root, node);
	data->ar = root;


	//printf("listsize %d\n", test_mylstsize(data->ar));

	return (0);
}


char **test_parse_args(char *line, int start, int end)
{
	char *str;
	char **array;

	str = ft_substr(line, start, end - start);
	array = ft_split(str, ' ');
	return (array);
}

t_args *test_get_t_arg(char *str)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));

	new->args = NULL;
	new->type = 0;
	new->next = NULL;
	return (new);
}

int test_parser(char *line, t_data *data)
{
	int count;
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
			ret = i + 1;
			end =  ret - 1;
			break;
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
	if (count == 0)
	{
		data->ar->args = ft_split(str, ' ');
	}
	else
	{
		get_args_list(str, data, count);
	}
	return (ret);
}