
#include "parseader.h"

int	quotes_counter(char *line, t_par *pars)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], "'", i) && \
			!(pars->dqc % 2))
			pars->sqc++;
		if (!behind_has_backslash(line, line[i], "\"", i) && \
			!(pars->sqc % 2))
			pars->dqc++;
		i++;
	}
	if (pars->sqc % 2 || pars->dqc % 2)
		return (-1);
	return (0);
}

void quotes_locations(char *line, t_par *pars, t_data *data) //TODO free 1
{
	pars->tmpi = 0;
	if (pars->dqc)
		pars->dql = (int *)malloc(sizeof(int) * pars->dqc);
	if (pars->sqc)
		pars->sql = (int *)malloc(sizeof(int) * pars->sqc);
	if (pars->sql == NULL || pars->dql == NULL)
		ft_exit(-1, data, 1);
	while (line[pars->tmpi] != '\0' && (pars->sqc || pars->dqc))
	{
		if (!behind_has_backslash(line, line[pars->tmpi], "'", pars->tmpi) && \
			!(pars->tmpdq % 2))
		{
			pars->sql[pars->sqi] = pars->tmpi;
			pars->sqi++;
			pars->tmpsq++;
		}
		if (!behind_has_backslash(line, line[pars->tmpi], "\"", pars->tmpi) && \
			!(pars->tmpsq % 2))
		{
			pars->dql[pars->dqi] = pars->tmpi;
			pars->dqi++;
			pars->tmpdq++;
		}
		pars->tmpi++;
	}
}

char get_dominator_quotes(char *string)
{
	int i;
	char q;

	i = 0;
	while (string[i] != '\0')
	{
		q = type_quotes(string, i);
		if (q)
			return (q);
		i++;
	}
	return (0);
}

int len_without_quotes(char *string, char q)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] != q)
			len++;
		i++;
	}
	return (len);
}

char *del_quotes(char *string, char quotes, t_data *data)
{
	char *new_string;
	int i;
	int j;

	i = 0;
	j = 0;
	new_string = (char *)malloc(len_without_quotes(string, quotes) + 1);
	if (new_string == NULL)
		ft_exit(-1, data, 1);
	while (string[i] != '\0')
	{
		if (string[i] != quotes)
		{
			new_string[j] = string[i];
			j++;
		}
		i++;
	}
	new_string[j] = '\0';
	free(string);
	return (new_string);
}
