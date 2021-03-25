#include "minishell.h"

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

void	ft_mylstadd_back(t_list_env **lst, t_list_env *new)
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

t_list_env	*ft_mylstnew(char *content)
{
	t_list_env *new;
	char *str;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (NULL == new)
		return (NULL);
	str = ft_strchr(content, '=');
	new->name = ft_substr(content, 0, str - content);
	new->content = ft_substr(content, str - content + 1, ft_strlen(content));
	if (str)
		new->has_equal = 1;
	else
		new->has_equal = 0;
	new->next = NULL;
	return (new);
}
