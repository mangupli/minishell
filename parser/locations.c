
#include "parseader.h"

void	pipes_locations(int i, t_par *pars)
{
	pars->ppl[pars->tmpp] = i;
	pars->tmpp++;
}

void	semicolon_locations(int i, t_par *pars)
{
	pars->sccl[pars->tmps] = i;
	pars->tmps++;
}

void	redirects_locations(int i, t_par *pars)
{
	pars->rl[pars->tmpr] = i;
	pars->tmpr++;
}

void	reverse_redirects_locations(int i, t_par *pars)
{
	pars->rrl[pars->tmprr] = i;
	pars->tmprr++;
}

void	locations(char *line, t_par *pars)
{
	int i;

	i = 0;
	allocate_locations(pars);
	while (line[i] != '\0' && (pars->scc || pars->ppc || pars->rc || pars->rrc))
	{
		if (!behind_has_backslash(line, line[i], "|;><", i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
		{
			if (line[i] == '|')
				pipes_locations(i, pars);
			if (line[i] == ';')
				semicolon_locations(i, pars);
			if (line[i] == '>')
				redirects_locations(i, pars);
			if (line[i] == '<')
				reverse_redirects_locations(i, pars);
		}
		i++;
	}
}