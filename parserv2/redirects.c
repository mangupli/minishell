#include "parser_head.h"

int redirects_counter(char *line, t_par *pars)
{
	int i;

	i = 0; //TODO проверка на валидность наличия аргументов после редиректов
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], '>', i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
			pars->rc++;
		i++;
	}
	return (0);
}

/*void redirects_locations(char *line, t_par *pars) //TODO free 4
{
	int i;

	i = 0;
	pars->tmpi = 0;
	if (pars->rc)
		pars->rl = (int *)malloc(sizeof(int) * pars->rc); // TODO защитить маллоки???
	while (line[i] != '\0' && pars->rc)
	{
		if (!behind_has_backslash(line, line[i], '>', i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
		{
			pars->rl[pars->tmpi] = i;
			pars->tmpi++;
		}
		i++;
	}
}*/

int reverse_redirects_counter(char *line, t_par *pars)
{
	int i;

	i = 0; //TODO проверка на валидность наличия аргументов после редиректов
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], '<', i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
			pars->rrc++;
		i++;
	}
	return (0);
}

void reverse_redirects_locations(char *line, t_par *pars) //TODO free 5
{
	int i;

	i = 0;
	pars->tmpi = 0;
	if (pars->rrc)
		pars->rrl = (int *)malloc(sizeof(int) * pars->rrc); // TODO защитить маллоки???
	while (line[i] != '\0' && pars->rrc)
	{
		if (!behind_has_backslash(line, line[i], '<', i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
		{
			pars->rrl[pars->tmpi] = i;
			pars->tmpi++;
		}
		i++;
	}
}