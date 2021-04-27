#include "minishell.h"

int		argslstsize(t_args *lst)
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

void args_clearlist(t_args **ar)
{
	t_args *tmp;

	if (ar)
	{
		while (*ar)
		{
			tmp = (*ar)->next;
			free_2d_array((*ar)->args, 0);
			free(*ar);
			*ar = tmp;
		}
	}
}

/*
** Created new node in the list of type t_args
** Arguments :
** (1)array of arguments
** (2)type '|' or 0
*/

t_args *arglstnew(char **args, char type)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));
	if (NULL == new)
		return (NULL);
	new->args = args;
	new->file[0] = -1;
	new->file[1] = -1;
	new->pid = -1;
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_args	*arglstlast(t_args *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

/*
** Adds new node in the back of the list of type t_args
** Arguments :
 * (1)address of the head
** (2)the pointer to the lode that should be added
*/

void	args_lstadd_back(t_args **lst, t_args *new)
{
	t_args	*tmp;

	if (lst)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
			arglstlast(tmp)->next = new;
	}
}