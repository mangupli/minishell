//
// Created by Moaning Stonehouse on 3/29/21.
//

#include "minishell.h"
#include "parseheaderv2.h"

int	quotes_counter(char *line, int i, t_par *pars)
{
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], '\'', i) && \
			!(pars->dqc % 2))
			pars->sqc++;
		if (!behind_has_backslash(line, line[i], '"', i) && \
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

void quotes_locations(char *line, int i, t_par *pars) //TODO free 1
{
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	if (pars->dqc)
		pars->dql = (int *)malloc(sizeof(int) * pars->dqc); // TODO защитить маллоки???
	if (pars->sqc)
		pars->sql = (int *)malloc(sizeof(int) * pars->sqc); // TODO защитить маллоки???
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], '\'', i) && \
			!(dq % 2))
		{
			pars->sql[pars->sqi] = i;
			pars->sqi++;
			sq++;
		}
		if (!behind_has_backslash(line, line[i], '"', i) && \
			!(sq % 2))
		{
			pars->dql[pars->dqi] = i;
			pars->dqi++;
			dq++;
		}
		i++;
	}
}
