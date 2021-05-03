#include "minishell.h"

void	envslst_clear(t_list_env **lst)
{
	t_list_env	*tmp;

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

/*
** There is a need for close_all_redir_fd(), in case parser returns -1
** -> it means something might be fucked up while opening files.
** But maybe it is unnecessary - think about it
*/

void	renew_data(t_data *data)
{
	close_all_redir_fd(data);
	args_clearlist(&data->ar);
}

void	close_2_fd(int *fd)
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

void	close_all_redir_fd(t_data *data)
{
	t_args	*tmp;

	tmp = data->ar;
	while (tmp)
	{
		close_2_fd(tmp->file);
		tmp = tmp->next;
	}
}

void	reset_fd(int *file_fd)
{
	close_2_fd(file_fd);
}
