#include "parseader.h"

void spaces_locations(int i, t_par *pars)
{
	pars->sl[pars->sci] = i;
	pars->sci++;
}

void spaces_worker(t_par *pars)
{
	int i;
	int count;

	i = 0;
	//separation_trash(pars);
	delete_excess_spaces(pars);
	if (pars->sl[pars->sc - 1] == pars->len - 1)
		pars->sl[pars->sc - 1] = -1;
	while (pars->sl[i] == -1)
		i++;
	if (i)
		pars->sl[i] = -1;
	if (pars->sl[0] == 0)
		pars->sl[0] = -1;
	i = 0;
	count = 0;
	while (i < pars->sc)
	{
		if (pars->sl[i] != -1)
			count++;
		i++;
	}
	new_spaces_array(pars, count);
}

void delete_excess_spaces(t_par *pars)
{
	int i;
	int j;

	i = 0;
	while (i < pars->sc)
	{
		j = i + 1;
		while (j < pars->sc)
		{
			if (pars->sl[j] - pars->sl[i] == 1 && pars->sl[j] != -1 && \
				pars->sl[i] != -1)
				pars->sl[i] = -1;
			j++;
		}
		i++;
	}
}

void new_spaces_array(t_par *pars, int count)
{
	int	*new_array;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_array = (int *)malloc(sizeof(int) * count); // TODO защити
	while (i < pars->sc)
	{
		if (pars->sl[i] != -1)
		{
			new_array[j] = pars->sl[i];
			j++;
		}
		i++;
	}
	pars->sc = count;
	free(pars->sl);
	pars->sl = new_array;
}

void separation_trash(t_par *pars)
{
	int i;
	int j;

	i = 0;
	while (i < pars->sc)
	{
		j = 0;
		while (j < (pars->scc + pars->ppc + pars->rc + pars->rrc))
		{
			if (pars->locs[j] - pars->sl[i] == 1 || \
					pars->sl[i] - pars->locs[j] == 1)
			{
				pars->sl[i] = -1;
				printf("\n|%d %d|\n", pars->locs[j], j);
				i++;
			}
			j++;
		}
		i++;
	}
}