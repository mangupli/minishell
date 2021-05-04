#include "minishell.h"

void	init_struct_a(t_state *a, int stdin_fd, int stdout_fd, t_data *data)
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

int	enable_mode(int fd)
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

int	rawline(char *buf, t_data *data)
{
	int	count;

	if (enable_mode(STDIN_FILENO) == -1)
		return (-1);
	count = edit(STDIN_FILENO, STDOUT_FILENO, buf, data);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_struct.orig_termios);
	ft_putstr_fd("\n", 1);
	return (count);
}
