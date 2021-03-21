#include "minishell.h"

void   edit_history_next(t_state *a, t_data *data, int dir)
{
	if (data->hist.len > 1)
	{
		free(data->hist.list[data->hist.len - 1 - a->index]);
		data->hist.list[data->hist.len - 1 - a->index] = ft_strdup(a->buf);
		if (dir == 0) // UP
			a->index += 1;
		else
			a->index -= 1; // DOWN
		if (a->index < 0)
		{
			a->index = 0;
			return;
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

int add_history(char *line, t_hist *h)
{
	char *cpy;

	if (h->list == NULL) {
		h->list = malloc(sizeof(char *) * h->maxlen);
		if (h->list == NULL)
			return (-1);
		ft_memset(h->list, 0, (sizeof(char *) * h->maxlen));
	}
	cpy = ft_strdup(line);
	if (h->len == h->maxlen)
	{
		free(h->list[0]);
		ft_memmove(h->list, h->list + 1,
			 sizeof(char *) * (h->maxlen - 1));
		h->len--;
	}
	h->list[h->len] = cpy;
	h->len++;
	return (0);
}

void save_history(char *file)
{

}
