
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
	{
		display_error("minishell", "syntax error", "unexpected token");
		return (-1);
	}
	return (0);
}

void quotes_locations(char *line, t_par *pars) //TODO free 1
{
	pars->tmpi = 0;
	if (pars->dqc)
		pars->dql = (int *)malloc(sizeof(int) * pars->dqc); // TODO защитить маллоки???
	if (pars->sqc)
		pars->sql = (int *)malloc(sizeof(int) * pars->sqc); // TODO защитить маллоки???
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

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\'')
			return ('\'');
		else if (string[i] == '"')
			return ('"');
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

char *del_single_quotes(char *string)
{
	char *new_string;
	int i;
	int j;

	i = 0;
	j = 0;
	new_string = (char *)malloc(len_without_quotes(string, '\'')); // Todo маллоки
	while (string[i] != '\0')
	{
		if (string[i] != '\'')
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
