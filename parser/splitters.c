#include "minishell.h"
#include "parseader.h"

void spaces_locations(int i, t_par *pars)
{
	pars->sl[pars->sci] = i;
	pars->sci++;
}

/*void	pipes_processors(t_data *data, char *str, int i)
{
	int		ind;
	char	*new_str;

	ind = str_has_pipe(&data->pars, 0, i);
	while (ind)
	{
		new_str = ft_substr(str, i, ind - i); // TODO free old str!
		
		ind = str_has_pipe(&data->pars, ind, i);
	}
}*/

void get_args(t_data *data, t_par *pars, int i, char *str)
{
	char type;
	t_args *node;

	type = 0;
	data->ar = NULL;
	if (i_inside_array(pars->ppl, pars->ppc, i, pars->next))
		type = '|';
	node = arglstnew(space_splitter(pars, str, i), type);
	args_lstadd_back(&data->ar, node);
	ft_free((void **)&str);
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
	int	x;

	j = 0;
	next = i_inside_array(pars->sl, pars->sc, i, pars->next);
	splits = (char **)malloc(sizeof(char *) * (splits_count(pars->sl, \
			pars->sc, i, pars->next))); // TODO проверить возможность сплитить вообще
	x = 0;
	while (pars->sc)
	{
		splits[j] = (char *)malloc(next - x + 1);
		x = get_str(new_str, splits[j], x, next);
		next = i_inside_array(pars->sl, pars->sc, next, pars->next);
		j++;
		if (!next)
		{
			splits[j] = (char *)malloc(pars->next - next + 1);
			get_str(new_str, splits[j], x, pars->next);
			break;
		}
	}
	splits[j + 1] = NULL;
	return (splits);
}

int get_str(char *new_str, char *splits, int ind, int next)
{
	int i;

	i = 0;
	while (ind <= next)
	{
		splits[i] = new_str[ind];
		ind++;
		i++;
	}
	splits[i] = '\0';
	return (ind);
}