#include "minishell.h"

/*
** Use the ESC [6n escape sequence to query the horizontal cursor position
** and return it. On error -1 is returned, on success the position of the
** cursor.
*/

int get_cursor_pos(int ofd)
{
	char buf[32];
	int cols;
	int rows;
	char c;
	int i;
	int ret;
	int pow;

	i = 0;
	c = 0;
	cols = 0;
	rows = 0;
	/* Report cursor location */
	ret = write(ofd, "\x1b[6n", 4);
	if (ret != 4)
		return (-1);
	/* Read the response: ESC [ rows ; cols R */
	while (c != 'R')
	{
		ret = read(0, &c, 1);
		if (ret != 1)
			return (-1);
		buf[i] = c;
		i++;
	}
	i -= 2;
	pow = 1;
	while(buf[i] != ';')
	{
		cols = cols + ( buf[i] - '0' ) * pow;
		i--;
		pow *= 10;
	}
	i--;
	pow = 1;
	while(buf[i] != '[')
	{
		rows = rows + ( buf[i] - '0' ) * pow;
		i--;
		pow *= 10;
	}
	return (cols);
}

/*
** Try to get the number of columns in the current terminal, or assume 80
** if it fails.
*/

int get_cols(int ofd)
{
	struct winsize ws;
	char seq[32];
	int start;
	int cols;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		/* ioctl() failed. Try to query the terminal itself. */
		/* Get the initial position so we can restore it later. */
		start = get_cursor_pos(ofd);
		if (start == -1)
			return (80);
		/* Go to right margin and get position. */
		if (write(ofd,"\x1b[999C",6) != 6)
			return (80);
		cols = get_cursor_pos(ofd);
		if (cols == -1)
			return (80);
		/* Restore position. */
		if (cols > start) {
			snprintf(seq, 32, "\x1b[%dD", cols-start); //TODO: rewrite with our functions
			write(ofd,seq,strlen(seq));
		}
		return (cols);
	}
	else
		return (ws.ws_col);
}