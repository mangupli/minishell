#include "minishell.h"

static void	calc_cols(char *buf, t_cursor *cur, int i)
{
	i -= 2;
	cur->pow = 1;
	while (buf[i] != ';')
	{
		cur->cols = cur->cols + (buf[i] - '0') * cur->pow;
		i--;
		cur->pow *= 10;
	}
}

/*
** the ESC [6n escape sequence ("\x1b[6n") to get the horizontal cursor position
** and return it. In response: ESC [ rows ; cols R
** On error -1 is returned, on success the position of the cursor (we get it to
** restore later)
*/

int	get_cursor_pos(int ofd)
{
	char		buf[32];
	int			ret;
	t_cursor	cur;
	int			i;

	i = 0;
	cur.c = 0;
	cur.cols = 0;
	cur.rows = 0;
	ret = write(ofd, "\x1b[6n", 4);
	if (ret != 4)
		return (-1);
	while (cur.c != 'R')
	{
		ret = read(0, &cur.c, 1);
		if (ret != 1)
			return (-1);
		buf[i] = cur.c;
		i++;
	}
	calc_cols(buf, &cur, i);
	return (cur.cols);
}

/*
** Try to get the number of columns in the current terminal, or assume 80
** if it fails.
** "\x1b[999C" -> goes to right margin and get position since C here means
** move cursor forward by n. D means move back
**
*/

int	get_cols(int ofd)
{
	struct winsize	ws;
	char			seq[32];
	int				start;
	int				cols;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		start = get_cursor_pos(ofd);
		if (start == -1)
			return (80);
		if (write(ofd, "\x1b[999C", 6) != 6)
			return (80);
		cols = get_cursor_pos(ofd);
		if (cols == -1)
			return (80);
		if (cols > start)
		{
			snprintf(seq, 32, "\x1b[%dD", cols - start);
			write(ofd, seq, ft_strlen(seq));
		}
		return (cols);
	}
	else
		return (ws.ws_col);
}
