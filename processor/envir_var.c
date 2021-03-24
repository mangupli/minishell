#include "minishell.h"

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

	new = (t_list_env *)malloc(sizeof(t_list_env) * 1);
	if (NULL == new)
		return (NULL);
	str = ft_strchr(content, '=');
	new->content = ft_substr(content, 0, str - content);
	new->content = ft_substr(content, str - content + 1, ft_strlen(content));
	if (str)
		new->has_equal = 1;
	else
		new->has_equal = 0;
	new->next = NULL;
	return (new);
}

t_list_env	*get_envlist(char **env)
{
	int i;
	t_list_env *new_list;

	i = -1;
	new_list = NULL;
	while (env[++i])
	{
		new_list = ft_mylstnew(env[i]);
		ft_mylstadd_back(&new_list, new_list);
	}
	return (new_list);
}