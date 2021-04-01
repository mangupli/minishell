#include "minishell.h"

int		ft_mylstsize(t_list_env *lst)
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


void	ft_mylstclear(t_list_env **lst)
{
	t_list_env *tmp;

	tmp = *lst;
	if (lst)
	{
		while (tmp)
		{
			free(tmp->content);
			free(tmp->name);
			free(tmp);
			tmp = tmp->next;
		}
	}
}

t_list_env	*ft_mylstlast(t_list_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	env_lst_addback(t_list_env **lst, t_list_env *new)
{
	t_list_env	*tmp;

	if (lst)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
			ft_mylstlast(tmp)->next = new;
	}
}

/*
** Created new node in the list of type t_list_env
** Arguments :
** (1) string that needs to be parsed, for example "PAGER=less"
**
** Function will create new node in the list with next parameters:
** name = "PAGER", content = "less", has equal = 1
*/

t_list_env	*envlstnew(char *string)
{
	t_list_env *new;
	char *str;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (NULL == new)
		return (NULL);
	str = ft_strchr(string, '=');
	new->name = ft_substr(string, 0, str - string);
	new->content = ft_substr(string, str - string + 1, ft_strlen(string));
	if (str)
		new->has_equal = 1;
	else
		new->has_equal = 0;
	new->next = NULL;
	return (new);
}

/*
** Created new node in the list of type t_list_env when name and content
** of environmental variable are already known.
** Arguments :
** (1) name
** (2) content
** (3) 0 or 1
*/

t_list_env	*envlistnew1(char *name, char *content, char has_equal)
{
	t_list_env *new;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (NULL == new)
		return (NULL);
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->has_equal = has_equal;
	new->next = NULL;
	return (new);
}
