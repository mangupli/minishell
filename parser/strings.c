
#include "parseader.h"

char *split_on_semicolon(char *line, int i, t_par *pars)
{
	int j;
	int end;
	char *str;

	j = 0;
	end = get_end(i, pars);
	str = (char *)malloc(end - i + 1);
	while (i < end)
	{
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	pars->next = end;
	return (str);
}

int get_end(int i, t_par *pars)
{
	int j;

	j = 0;
	while (j < pars->scc)
	{
		if (i < pars->sccl[j])
			return (pars->sccl[j]);
		j++;
	}
	return (pars->len);
}

void	counter(char *line, t_par *pars)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!behind_has_backslash(line, line[i], "|;>< ", i) && \
				!(im_in_quotes(i, pars->sqc, pars->sql)) && \
				!(im_in_quotes(i, pars->dqc, pars->dql)))
		{
			if (line[i] == '|')
				pars->ppc++;
			if (line[i] == ';')
				pars->scc++;
			if (line[i] == '>')
				pars->rc++;
			if (line[i] == '<')
				pars->rrc++;
			if (line[i] == ' ')
				pars->sc++;
		}
		i++;
	}
}

void	allocate_locations(t_par *pars) //TODO free 2
{
	if (pars->scc)
		pars->sccl = (int *)malloc(sizeof(int) * pars->scc);
	if (pars->ppc)
		pars->ppl = (int *)malloc(sizeof(int) * pars->ppc);
	if (pars->rc)
		pars->rl = (int *)malloc(sizeof(int) * pars->rc);
	if (pars->rrc)
		pars->rrl = (int *)malloc(sizeof(int) * pars->rrc);
	if (pars->sc)
		pars->sl = (int *)malloc(sizeof(int) * pars->sc);
	if (pars->scc || pars->ppc || pars->rc || pars->rrc)
		pars->locs = (int *)malloc(sizeof(int) * (pars->scc + pars->ppc + \
											pars->rc + pars->rrc + 1));
}

void	locations_compile(t_par *pars)
{
	int i;

	i = fill_locs_array(pars, pars->sccl, 0, pars->scc);
	i = fill_locs_array(pars, pars->ppl, i, pars->ppc);
	i = fill_locs_array(pars, pars->rl, i, pars->rc);
	fill_locs_array(pars, pars->rrl, i, pars->rrc);
	sorted_array(pars);
	pars->locs[pars->scc + pars->ppc + pars->rc + pars->rrc] = -1;
}

