#include "minishell.h"

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

static int	ab_joinstr(t_apbuf *ab, const char *str, int len)
{
	char	*new;

	new = malloc(sizeof(char) * (ab->len + len));
	if (new == NULL)
		return (-1);
	ft_memcpy(new, ab->b, ab->len);
	ft_memcpy(new + ab->len, str, len);
	if (ab->b)
		ab_free(ab);
	ab->b = new;
	ab->len += len;
	return (0);
}

/*
** Rewrite the currently edited line accordingly to the buffer content,
** cursor position, and number of columns of the terminal.
*/

void	refresh_line(t_state *a)
{
	char	*keys;
	t_apbuf	ab;
	size_t	len;
	size_t	pos;
	char	*buf;
	int		res;

	len = a->len;
	pos = a->pos;
	buf = a->buf;
	while ((a->plen + pos) >= a->cols)
	{
		buf++;
		len--;
		pos--;
	}
	while ((a->plen + len) >= a->cols)
		len--;
	ab_init(&ab);
	keys = ft_calloc(64, sizeof(char));
	if (keys == NULL)
		return ;
	//ft_joinstr();

	keys = ft_strcpy(keys, "\r");
	ab_joinstr(&ab, keys, ft_strlen(keys));
	ab_joinstr(&ab, a->prompt, ft_strlen(a->prompt));
	ab_joinstr(&ab, buf, len);
	keys = ft_strcpy(keys, "\x1b[0K");
	ab_joinstr(&ab, keys, ft_strlen(keys));
	res = (int)(pos + a->plen);

	len = ft_numlen(res);
	keys[0] = '\r';
	keys[1] = '\x1b';
	keys[2] = '[';
	keys[2 + len + 1] = 'C';
	keys[2 + len + 2] = '\0';
	while (len)
	{
		keys[2 + len] = (res % 10) + '0';
		res /= 10;
		len--;
	}
	ab_joinstr(&ab, keys, ft_strlen(keys));
	write(a->ofd, ab.b, ab.len);
	ab_free(&ab);
	free(keys);
}
