#include "parseader.h"

void spaces_worker(t_par *pars, char *line)
{
	int i;
	int count;

	i = 0;
	while (line[i] == ' ')
		i++;
	delete_excess_spaces(pars, i);
	if (pars->sl[pars->sc - 1] == pars->len - 1)
		pars->sl[pars->sc - 1] = -1;
	i = 0;
	count = 0;
	separation_trash(pars);
	back_separation_trash(line, pars);
	while (i < pars->sc)
	{
		if (pars->sl[i] != -1)
			count++;
		i++;
	}
	new_spaces_array(pars, count);
}

void delete_excess_spaces(t_par *pars, int false_space)
{
	int i;
	int j;

	i = 0;
	while (i < pars->sc)
	{
		j = i + 1;
		while (j < pars->sc)
		{
			if ((pars->sl[j] - pars->sl[i] == 1 && pars->sl[j] != -1 && \
				pars->sl[i] != -1) || pars->sl[i] <= false_space)
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
			if (pars->locs[j] - pars->sl[i] == 1)
				pars->sl[i] = -1;
			j++;
		}
		i++;
	}
}

void back_separation_trash(char *line, t_par *pars)
{
	int i;
	int j;

	i = pars->sc - 1;
	while (i >= 0)
	{
		if (pars->sl[i] != -1)
		{
			j = pars->sl[i] - 1;
			while (j >= 0)
			{
				if (ft_strchr("|;><", line[j]))
				{
					pars->sl[i] = -1;
					break ;
				}
				else if (line[j] != ' ')
					break ;
				j--;
			}
		}
		i--;
	}
}