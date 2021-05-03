#include "minishell.h"

/*
** dir == 0 -> UP | dir == 1 -> DOWN
*/

void	edit_history_next(t_state *a, t_data *data, int dir)
{
	if (data->hist.len > 1)
	{
		free(data->hist.list[data->hist.len - 1 - a->index]);
		data->hist.list[data->hist.len - 1 - a->index] = ft_strdup(a->buf);
		if (dir == 0)
			a->index += 1;
		else
			a->index -= 1;
		if (a->index < 0)
		{
			a->index = 0;
			return ;
		}
		else if (a->index >= data->hist.len)
		{
			a->index = data->hist.len - 1;
			return ;
		}
		ft_strncpy(a->buf, data->hist.list[data->hist.len - 1 - a->index],
			 a->buflen);
		a->buf[a->buflen - 1] = '\0';
		a->len = ft_strlen(a->buf);
		a->pos = ft_strlen(a->buf);
		refresh_line(a);
	}
}

int	add_history(char *line, t_hist *h)
{
	char	*cpy;

	if (h->list == NULL)
	{
		h->list = malloc(sizeof(char *) * h->maxlen);
		if (h->list == NULL)
			return (-1);
		ft_memset(h->list, 0, (sizeof(char *) * h->maxlen) + 1);
	}
	cpy = ft_strdup(line);
	if (h->len == h->maxlen)
	{
		ft_free((void **)&h->list[0]);
		ft_memmove(h->list, h->list + 1,
			 sizeof(char *) * (h->maxlen - 1));
		h->len--;
	}
	h->list[h->len] = cpy;
	h->len++;
	return (0);
}

void	load_history(t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	fd = open("minishell_history.txt", O_RDONLY, 700);
	if (fd < 0)
		return ;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		add_history(line, &data->hist);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret < 0)
		return ;
	free(line);
	close(fd);
}

void	save_history(t_data *data)
{
	int		i;
	int		fd;
	char	**history;

	history = data->hist.list;
	fd = open("minishell_history.txt", O_RDWR | O_CREAT | O_TRUNC, 0700);
	if (fd == -1)
		display_error("minishell", NULL, strerror(errno));
	else
	{
		i = -1;
		while (history[++i])
		{
			ft_putstr_fd(history[i], fd);
			ft_putstr_fd("\n", fd);
		}
		close(fd);
	}
}
