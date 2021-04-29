#include "minishell.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int check_symbols(char *str)
{
	int i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

t_list_env *strdup_list(t_list_env **src)
{
	t_list_env *new;
	t_list_env *tmp;
	t_list_env *node;

	tmp = *src;
	new = NULL;
	while (tmp)
	{
		node = envlistnew1(tmp->name, tmp->content, tmp->has_equal);
		env_lst_addback(&new, node);
		tmp = tmp->next;
	}
	return (new);
}

t_list_env *sort_list(t_list_env *src)
{
	t_list_env *root;
	t_list_env *new_root;
	t_list_env *node;
	t_list_env *current;

	root = strdup_list(&src);
	new_root = NULL;
	while (root)
	{
		node = root;
		root = root->next;
		if (!new_root || ft_strcmp(node->name, new_root->name) < 0)
		{
			node->next = new_root;
			new_root = node;
		}
		else
		{
			current = new_root;
			while (current->next && ft_strcmp(node->name, current->next->name) >= 0)
				current = current->next;
			node->next = current->next;
			current->next = node;
		}
	}
	return (new_root);
}

void 	free_2d_array(char **array, int start)
{
	int i;

	i = start;
	while (array[i] != NULL)
	{
		ft_free((void **)&array[i]);
		i++;
	}
	if (!start)
	{
		free(array);
		array = NULL;
	}
}