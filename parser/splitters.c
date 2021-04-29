#include "minishell.h"
#include "parseader.h"

char **splitter(t_par *pars, char *line, int i, int location)
{
	int j;
	int next;
	char **splits;
	int count;

	j = 0;
	next = i_inside_array(pars->sl, pars->sc, i, location);
	count = splits_count(pars->sl, pars->sc, i, location);
	splits = (char **)malloc(sizeof(char *) * count);
	while (j + 2 < count)
	{
		splits[j] = (char *)malloc(next - i + 2);
		i = get_str(pars, splits[j], i, next);
		next = i_inside_array(pars->sl, pars->sc, next, location);
		j++;
	}
	splits[j] = (char *)malloc(location - next + 2);
	get_str(pars, splits[j], i, location - 1);
	splits[j + 1] = NULL;
	return (splits);
}

int get_str(t_par *pars, char *splits, int ind, int next)
{
	int i;
	int r;
	int rr;
	int stop;

	i = 0;
	r = i_inside_array(pars->rl, pars->rc, ind, pars->next);
	rr = i_inside_array(pars->rrl, pars->rrc, ind, pars->next);
	stop = next;
	if (r && next > r)
		stop = r;
	else if (rr && next > rr)
		stop = rr;
	while (ind <= next)
	{
		if (ind <= stop)
			splits[i] = pars->line_copy[ind];
		i++;
		ind++;
	}
	splits[i] = '\0';
	if (stop != next || splits[0] == '>' || splits[0] == '<')
		;// TODO здесь нужно найти название файлов
	return (ind);
}
