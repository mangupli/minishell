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

static void	backspace_edit(t_state *a)
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


static void init_struct_a(t_state *a, int stdin_fd, int stdout_fd, t_data *data)
{
	a->ifd = stdin_fd;
	a->ofd = stdout_fd;
	if (data->add_to_prompt != NULL)
		a->prompt = ft_strjoin(data->add_to_prompt, data->prompt);
	else
		a->prompt = data->prompt;
	a->plen = ft_strlen(a->prompt);
	a->buflen = MAX_LINE;
	a->pos = 0;
	a->len = 0;
	a->cols = get_cols(stdout_fd);
	a->index = 0;
	a->buflen--;
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

static int	edit(int stdin_fd, int stdout_fd, char *buf, t_data *data)
{
	t_state	a;
	int		ret;
	char	c;
	int		bytes;
	char	keys[3];

	init_struct_a(&a, stdin_fd, stdout_fd, data);
	a.buf = buf;
	a.buf[0] = '\0';
	add_history("", &data->hist);
	ret = write(a.ofd, a.prompt, a.plen);
	if (ret == -1)
		return (-1);
	while (1)
	{
		bytes = read(a.ifd, &c, 1);
		if (bytes <= 0)
			return (a.len);
		if (c == ENTER)
		{
			data->hist.len--;
			ft_free((void **)&data->hist.list[data->hist.len]);
			if (g_struct.echo_n == 1)
				ft_free((void **)&a.prompt);
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
			data->hist.len--;
			ft_free((void **)&data->hist.list[data->hist.len]);
			if (g_struct.echo_n == 1)
				ft_free((void **)&a.prompt);
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
	return (a.len);
}

/*
** g_struct.orig_termious -> the original mode which we will modify
** (BRKINT | ICRNL | INPCK | ISTRIP | IXON) -> input modes:
**                      no break, no CR to NL, no parity check, no strip char,
**                      no start/stop output control.
** (OPOST) -> disable post processing
** (CS8) -> set 8 bit chars
** (ECHO | ICANON | IEXTEN | ISIG) -> local modes:
** 								choing off, canonical off, no extended functions,
**								no signal chars (^Z,^C)
** raw.c_cc[VMIN] and raw.c_cc[VTIME] ->
** control chars - set return condition: min number of bytes and timer.
** We want read to return every single byte, without timeout. 1 byte, no timer
** tcsetattr(fd, TCSAFLUSH, &raw) -> put terminal in raw mode after flushing
*/

static int	enable_mode(int fd)
{
	struct termios	raw;

	if (tcgetattr(fd, &g_struct.orig_termios) == -1)
	{
		errno = ENOTTY;
		return (-1);
	}
	raw = g_struct.orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &raw) < 0)
	{
		errno = ENOTTY;
		return (-1);
	}
	return (0);
}

/*
** This function calls the line editing function edit() using
** the STDIN file descriptor set in raw mode.
*/

static int	rawline(char *buf, t_data *data)
{
	int	count;

	if (enable_mode(STDIN_FILENO) == -1)
		return (-1);
	count = edit(STDIN_FILENO, STDOUT_FILENO, buf, data);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_struct.orig_termios);
	ft_putstr_fd("\n", 1);
	return (count);
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
