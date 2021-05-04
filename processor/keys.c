#include "minishell.h"

void	backspace_edit(t_state *a)
{
	if (a->pos > 0 && a->len > 0)
	{
		ft_memmove(a->buf + a->pos - 1, a->buf + a->pos, a->len - a->pos);
		a->pos--;
		a->len--;
		a->buf[a->len] = '\0';
		refresh_line(a);
	}
}

int	ft_ctrl_c(char *buf)
{
	errno = EAGAIN;
	g_struct.status = 1;
	buf[0] = '\0';
	return (0);
}

int	ft_esc(char *keys, t_data *data, t_state *a)
{
	if (read(a->ifd, keys, 2) == -1)
		return (-2);
	if (keys[0] == '[')
	{
		if (keys[1] == 'A')
			edit_history_next(a, data, 0);
		if (keys[1] == 'B')
			edit_history_next(a, data, 1);
	}
	return (0);
}
