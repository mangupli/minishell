#include "minishell.h"

/*
** Insert the character 'c' at cursor current position.
*/

static int	edit_insert(t_state *a, char c)
{
	if (a->len < a->buflen)
	{
		if (a->len == a->pos)
		{
			a->buf[a->pos] = c;
			a->pos++;
			a->len++;
			a->buf[a->len] = '\0';
			refresh_line(a);
		}
		else
		{
			ft_memmove(a->buf + a->pos + 1, a->buf + a->pos, a->len - a->pos);
			a->buf[a->pos] = c;
			a->len++;
			a->pos++;
			a->buf[a->len] = '\0';
			refresh_line(a);
		}
	}
	return (0);
}

/*
** 1) char exit tells if we need to putstr "exit" before escaping minishell
** 2) char d tells us what to return -> if CTRL_D was pressed -> then -1
** otherwise everything is ok and we return current edited line length
*/

static int	one_step_back(t_data *data, t_state *a, char exit, char d)
{
	data->hist.len--;
	ft_free((void **)&data->hist.list[data->hist.len]);
	if (g_struct.echo_n == 1)
		ft_free((void **)&a->prompt);
	if (exit)
		ft_putstr_fd("exit", 1);
	if (d)
		return (-1);
	return (a->len);
}

static int	what_symbol(t_state *a, t_data *data, char c, char *buf)
{
	char	keys[3];

	if (c == ENTER)
		return (one_step_back(data, a, 0, 0));
	else if (c == CTRL_C)
		return (ft_ctrl_c(buf));
	else if (c == BACKSPACE)
		backspace_edit(a);
	else if (c == CTRL_D)
	{
		if (a->len)
			return (0);
		return (one_step_back(data, a, 1, 1));
	}
	else if (c == CTRL_BACKSLASH)
		return (0);
	else if (c == ESC)
	{
		if (ft_esc(keys, data, a))
			return (-2);
	}
	else
		edit_insert(a, c);
	return (0);
}

/*
**This function is the core of the line editing capability of linenoise.
** It expects 'orig_fd' to be already in "raw mode" so that every key pressed
** will be returned ASAP to read().
**
** The resulting string is put into 'buf' when the user type enter, or
** when ctrl+d is typed.
**
** The function returns the length of the current buffer.
** The latest history entry is always our current buffer, that
** initially is just an empty string. That's why we add_history() before input.
**
** a.buf[0] = '\0' -> buffer starts empty
**
** Sequences: Esc[A == UP arrow key | ESC[B == DOWN arrow key
*/

int	edit(int stdin_fd, int stdout_fd, char *buf, t_data *data)
{
	t_state	a;
	int		ret;
	char	c;

	init_struct_a(&a, stdin_fd, stdout_fd, data);
	a.buf = buf;
	a.buf[0] = '\0';
	add_history("", &data->hist);
	if (write(a.ofd, a.prompt, a.plen) == -1)
		return (-1);
	while (1)
	{
		if (read(a.ifd, &c, 1) <= 0)
			return (a.len);
		ret = what_symbol(&a, data, c, buf);
		if (c == CTRL_C)
			return (0);
		if (c == ENTER)
			return (ret);
		if (ret == -1)
			return (-1);
		if (ret == -2)
			break ;
	}
	return (a.len);
}

char	*ft_readline(t_data *data)
{
	char	buf[MAX_LINE];
	int		ret;

	ret = rawline(buf, data);
	if (ret == -1)
		return (NULL);
	return (ft_strdup(buf));
}

/* while (1) that worked before norm
while (1)
{
 	bytes = read(a.ifd, &c, 1);
	if (bytes <= 0)
		return (a.len);
	if (c == ENTER)
	{
		one_step_back(data, &a);
		return (a.len);
	}
	else if (c == CTRL_C)
	{
		errno = EAGAIN;
		g_struct.status = 1;
		buf[0] = '\0';
		return (0);
	}
	else if (c == BACKSPACE)
		backspace_edit(&a);
	else if (c == CTRL_D)
	{
		one_step_back(data, &a);
		ft_putstr_fd("exit", 1);
		return (-1);
	}
	else if (c == CTRL_BACKSLASH)
		continue ;
	else if (c == ESC)
	{
		ret = read(a.ifd, keys, 2);
		if (ret == -1)
			break ;
		if (keys[0] == '[')
		{
			if (keys[1] == 'A')
				edit_history_next(&a, data, 0);
			if (keys[1] == 'B')
				edit_history_next(&a, data, 1);
		}
	}
	else
	{
		if (edit_insert(&a, c))
			return (-1);
	}
}
 */
