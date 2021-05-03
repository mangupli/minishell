#include "parseader.h"

int	validations(char *line, t_par *pars)
{
	int i;
	int next;

	locations_compile(pars);
	if (has_twinks_redirects(pars))
		return (-1);
	i = 0;
	while (pars->locs[i] != -1 && (pars->ppc || pars->rc || pars->rrc || \
			pars->scc))
	{
		if (pars->locs[i + 1] == -1)
			next = pars->len;
		else
			next = pars->locs[i + 1];
		if (between_only_spaces_or_twinks(line, pars->locs[i], next, pars->len))
			return (-1);
		i++;
	}
	return (0);
}

void	sorted_array(t_par *pars)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < (pars->scc + pars->ppc + pars->rc + pars->rrc))
	{
		j = i + 1;
		while (j < (pars->scc + pars->ppc + pars->rc + pars->rrc))
		{
			if (pars->locs[i] > pars->locs[j])
			{
				tmp = pars->locs[i];
				pars->locs[i] = pars->locs[j];
				pars->locs[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	fill_locs_array(t_par *pars, int *src, int i, int stop)
{
	int j;

	j = 0;
	while (j < stop)
	{
		pars->locs[i] = src[j];
		j++;
		i++;
	}
	return (i);
}

bool	has_twinks_redirects(t_par *pars)
{
	int i;

	i = 0;
	while (i + 2 < pars->rc)
	{
		if ((pars->rl[i + 2] - pars->rl[i + 1]) == 1 && \
			(pars->rl[i + 1] - pars->rl[i]) == 1)
			return (True);
		i++;
	}
	i = 0;
	while (i + 1 < pars->rrc)
	{
		if ((pars->rrl[i + 1] - pars->rrl[i]) == 1)
			return (True);
		i++;
	}
	return (False);
}

bool	between_only_spaces_or_twinks(char *line, int start, int stop, int len)
{
	if (stop - start == 1 && line[start] != '>' && line[stop] != '>' && \
						line[start] != '<' && line[stop] != '<')
		return (True);
	if ((line[start] == '>' && line[stop] == '>' && stop - start == 1) || \
			(stop == len && line[start] == ';') || \
			(stop - start == 1 && (line[start] == '>' || line[stop] == '>' ||
			(line[start] == '<' || line[stop] == '<'))))
		return (False);
	start++;
	while (start < stop)
	{
		if (line[start] != ' ')
			return (False);
		start++;
	}
	return (True);
}
