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
		splits[j] = (char *)malloc(next - i + 1);
		i = get_str(line, splits[j], i, next);
		next = i_inside_array(pars->sl, pars->sc, next, location);
		j++;
	}
	splits[j] = (char *)malloc(location - next + 1);
	get_str(line, splits[j], i, location - 1);
	splits[j + 1] = NULL;
	return (splits);
}

int get_str(char *line, char *splits, int ind, int next)
{
	int i;

	i = 0;
	while (ind <= next)
	{
		splits[i] = line[ind];
		ind++;
		i++;
	}
	splits[i] = '\0';
	return (ind);
}
