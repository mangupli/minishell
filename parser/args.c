#include "minishell.h"
#include "parseader.h"

void get_args(t_data *data, t_par *pars, int i, char *line)
{
	t_args *node;
	int location;
	char **strings;

	data->ar = NULL;
	location = i_inside_array(pars->ppl, pars->ppc, i, pars->next);
	while (location)
	{
		strings = splitter(pars, line, i, location);
		args_normalizer(strings, data);
		node = arglstnew(strings, '|');
		args_lstadd_back(&data->ar, node);
		i = location;
		location = i_inside_array(pars->ppl, pars->ppc, i, pars->next);
	}
	strings = splitter(pars, line, i, pars->next);
	args_normalizer(strings, data);
	node = arglstnew(strings, 0);
	args_lstadd_back(&data->ar, node);
}

void args_normalizer(char **splits, t_data *data)
{
	int i;
	char *tmp;

	i = 0;
	while (splits[i] != NULL)
	{
		tmp = splits[i];
		splits[i] = ft_strtrim(splits[i], " |"); // todo маллоки
		free(tmp);
		splits[i] = quotes_worker(splits[i]);
		i++;
	}
}

char *quotes_worker(char *string)
{
	char q;

	q = get_dominator_quotes(string);
	if (q == '\'')
		return del_single_quotes(string);
	return (string);
}
