#include "parseader.h"


void	pipes_processors(t_par *pars)
{
	while (str_has_pipe(pars))
	{

	}
}


int		str_has_pipe(t_par *pars)
{
	int i;

	i = 0;
	while (i < pars->ppc)
	{
		if (pars->ppl[i] < pars->next)
			return (i);
		i++;
	}
	return (0);
}

