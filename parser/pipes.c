#include "minishell.h"
#include "parseader.h"

void spaces_locations(int i, t_par *pars)
{
	pars->sl[pars->sci] = i;
	pars->sci++;
}

void	pipes_processors(t_data *data, char *str, int i)
{
	int		ind;
	char	*new_str;

	ind = str_has_pipe(&data->pars, 0, i);
	while (ind)
	{
		new_str = ft_substr(str, i, ind - i); // TODO free old str!
		
		ind = str_has_pipe(&data->pars, ind, i);
	}
}

int		str_has_pipe(t_par *pars, int ind, int start)
{
	while (ind < pars->ppc)
	{
		if (pars->ppl[ind] < pars->next && pars->ppl[ind] > start)
			return (ind);
		ind++;
	}
	return (0);
}

char **space_splitter(t_par *pars, char *new_str, int i)
{
	int j;
	int next;
	char **splits;

	j = 0;
	next = i_inside_array(pars->sl, pars->sc, i, pars->next);
	splits = (char **)malloc(sizeof(char *) * (splits_count(pars->sl, \
			pars->sc, i, pars->next) + 1)); // TODO проверить возможность сплитить вообще
	while (next)
	{

		next = i_inside_array(pars->sl, pars->sc, next, pars->next);
	}
	return NULL;
}