#include "minishell.h"
#include "parseader.h"

int	set_redir_fd(char *red_type, char *filename, t_args *ar)
{
	if (!ft_strcmp(red_type, "<"))
		return (reverse_redirect_open(filename, ar));
	if (!ft_strcmp(red_type, ">>"))
		return (double_redirect_open(filename, ar));
	if (!ft_strcmp(red_type, ">"))
		return (redirect_open(filename, ar));
	return (0);
}

int reverse_redirect_open(char *filename, t_args *ar)
{
	if (ar->file[0] >= 0)
		close(ar->file[0]);
	ar->file[0] = open(filename, O_RDONLY);
	if (ar->file[0] < 0)
	{
		display_error("minishell", filename,
				"No such file or directory");
		g_struct.status = 1;
		return (-2);
	}
	return (0);
}

int double_redirect_open(char *filename, t_args *ar)
{
	if (ar->file[1] >= 0)
		close(ar->file[1]);
	ar->file[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (ar->file[1] < 0)
	{
		display_error("minishell", filename,
					  strerror(errno));
		g_struct.status = 1;
		return (-2);
	}
	return (0);
}

int redirect_open(char *filename, t_args *ar)
{
	if (ar->file[1] >= 0)
		close(ar->file[1]);
	ar->file[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (ar->file[1] < 0)
	{
		display_error("minishell", filename,
				strerror(errno));
		g_struct.status = 1;
		return (-2);
	}
	return (0);
}

void redirects_extractor(char **splits, int i)
{
	int j;

	j = i;
	while (splits[j] != NULL)
		j++;
	while (j > i)
	{
		splits[j - 1] = splits[j];
		j--;
	}
}