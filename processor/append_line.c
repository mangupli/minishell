#include "minishell.h"

/*
static void	ab_init(t_apbuf *ab)
{
	ab->b = NULL;
	ab->len = 0;
}

static void	ab_free(t_apbuf *ab)
{
	free(ab->b);
	ab->b = NULL;
}
 */

static int	ab_joinstr(t_apbuf *ab, const char *str, int len)
{
	char	*new;

	new = malloc(sizeof(char) * (ab->len + len));
	if (new == NULL)
		return (-1);
	ft_memcpy(new, ab->b, ab->len);
	ft_memcpy(new + ab->len, str, len);
	if (ab->b)
	{
		free(ab->b);
		ab->b = NULL;
	}
	ab->b = new;
	ab->len += len;
	return (0);
}

static void	move_cursor(t_line *line, t_apbuf *ab, t_state *a)
{
	line->res = (int)(line->pos + a->plen);
	line->len = ft_numlen(line->res);
	line->keys[0] = '\r';
	line->keys[1] = '\x1b';
	line->keys[2] = '[';
	line->keys[2 + line->len + 1] = 'C';
	line->keys[2 + line->len + 2] = '\0';
	while (line->len)
	{
		line->keys[2 + line->len] = (line->res % 10) + '0';
		line->res /= 10;
		line->len--;
	}
	ab_joinstr(ab, line->keys, ft_strlen(line->keys));
}

static void	prepare_buf(t_line *line, t_apbuf *ab, t_state *a)
{
	line->keys = ft_strcpy(line->keys, "\r");
	ab_joinstr(ab, line->keys, ft_strlen(line->keys));
	ab_joinstr(ab, a->prompt, ft_strlen(a->prompt));
	ab_joinstr(ab, line->buf, line->len);
	line->keys = ft_strcpy(line->keys, "\x1b[0K");
	ab_joinstr(ab, line->keys, ft_strlen(line->keys));
}

/*
** Rewrite the currently edited line accordingly to the buffer content,
** cursor position, and number of columns of the terminal.
** "\x1b[0K" -> erases everything to the right
** "\x1b[%dC" -> Move cursor forward by %d
*/

void	refresh_line(t_state *a)
{
	t_apbuf	ab;
	t_line	line;

	line.len = a->len;
	line.pos = a->pos;
	line.buf = a->buf;
	while ((a->plen + line.pos) >= a->cols)
	{
		line.buf++;
		line.len--;
		line.pos--;
	}
	while ((a->plen + line.len) >= a->cols)
		line.len--;
	ab.b = NULL;
	ab.len = 0;
	line.keys = ft_calloc(64, sizeof(char));
	if (line.keys == NULL)
		return ;
	prepare_buf(&line, &ab, a);
	move_cursor(&line, &ab, a);
	write(a->ofd, ab.b, ab.len);
	free(ab.b);
	ab.b = NULL;
	free(line.keys);
}
