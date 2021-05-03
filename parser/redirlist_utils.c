#include "minishell.h"
#include "parseader.h"

t_list_redir	*redirlstnew(char *filename, char *red_type)
{
	t_list_redir *new;

	new = (t_list_redir *)malloc(sizeof(t_list_redir));
	if (NULL == new)
		return (NULL);
	new->filename = filename;
	new->red_type = red_type;
	new->next = NULL;
	return (new);
}

int		redirlstsize(t_list_redir *lst)
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


void	redirslst_clear(t_list_redir **lst)
{
	t_list_redir *tmp;

	tmp = *lst;
	if (lst)
	{
		while (tmp)
		{
			free(tmp->filename);
			free(tmp->red_type);
			free(tmp);
			tmp = tmp->next;
		}
	}
}

static t_list_redir *redirlstlast(t_list_redir *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	redir_lst_addback(t_list_redir **lst, t_list_redir *new)
{
	t_list_redir	*tmp;

	if (lst)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
			redirlstlast(tmp)->next = new;
	}
}