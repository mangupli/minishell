#include "minishell.h"
#include "parseader.h"

char	**splitter(t_data *data, int i, int location)
{
	int		j;
	int		next;
	char	**splits;
	int		count;

	j = 0;
	next = i_inside_array(data->pars.sl, data->pars.sc, i, location);
	count = splits_count(data->pars.sl, data->pars.sc, i, location);
	splits = (char **)malloc(sizeof(char *) * count);
	while (j + 2 < count)
	{
		splits[j] = (char *)malloc(next - i + 2);
		if (splits[j] == NULL)
			ft_exit(-1, data, 1);
		i = get_str(&data->pars, splits[j], i, next);
		next = i_inside_array(data->pars.sl, data->pars.sc, next, location);
		j++;
	}
	splits[j] = (char *)malloc(location - next + 2);
	if (splits[j] == NULL)
		ft_exit(-1, data, 1);
	get_str(&data->pars, splits[j], i, location - 1);
	splits[j + 1] = NULL;
	return (splits);
}

int	get_str(t_par *pars, char *splits, int ind, int next)
{
	int	i;

	i = 0;
	pars->xr = i_inside_array(pars->rl, pars->rc, ind, pars->next);
	pars->xrr = i_inside_array(pars->rrl, pars->rrc, ind, pars->next);
	pars->xstop = next + 1;
	if (pars->xr && next > pars->xr)
		pars->xstop = pars->xr - 1;
	else if (pars->xrr && next > pars->xrr)
		pars->xstop = pars->xrr - 1;
	while (ind <= next)
	{
		if (ind == pars->xstop && pars->line_copy[ind] != '>')
			splits[i] = '\0';
		else
			splits[i] = pars->line_copy[ind];
		i++;
		ind++;
	}
	splits[i] = '\0';
	if (splits[0] == '>' || splits[0] == '<')
		pars->redirs = ft_strdup(splits);
	else if (pars->xstop != next + 1)
		pars->redirs = ft_strdup(&splits[ft_strlen(splits) + 1]);
	return (ind);
}

int	file_opener(char *string_with_file, t_data *data, t_args *ar)
{
	int		i;
	char	*red_type;
	char	*filename;
	int		r;

	i = 0;
	filename = NULL;
	while (i < ft_strlen(string_with_file))
	{
		red_type = (char *)malloc(3);
		if (red_type == NULL)
			ft_exit(-1, data, 1);
		i = redirect_type(string_with_file, red_type, i);
		i = get_filename(string_with_file, &filename, i, data);
		r = set_redir_fd(red_type, filename, ar);
		free(filename);
		free(red_type);
		if (r == -2)
			return (-2);
	}
	return (0);
}

int	redirect_type(char *text, char *red_type, int i)
{
	int	j;

	while (text[i] == ' ')
		i++;
	j = 0;
	while (text[i] == '>' || text[i] == '<')
	{
		red_type[j] = text[i];
		j++;
		i++;
	}
	red_type[j] = '\0';
	while (text[i] == ' ')
		i++;
	return (i);
}

int	get_filename(char *text, char **filename, int i, t_data *data)
{
	int	len;
	int	j;

	len = 0;
	while (text[i] != ' ' && text[i] != ';' && text[i] != '|' \
			&& text[i] != '\\' && text[i] != '>' && text[i] != '<')
	{
		i++;
		len++;
	}
	*filename = (char *)malloc(len + 1);
	if (*filename == NULL)
		ft_exit(-1, data, 1);
	j = 0;
	i -= len;
	while (j < len)
	{
		filename[0][j] = text[i];
		j++;
		i++;
	}
	filename[0][j] = '\0';
	while (text[i] == ' ')
		i++;
	return (i);
}
