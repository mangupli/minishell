#include "minishell.h"
#include "parseader.h"

int get_args(t_data *data, t_par *pars, int i, char *line)
{
	t_args *node;
	int location;
	char **strings;

	data->ar = NULL;
	location = i_inside_array(pars->ppl, pars->ppc, i, pars->next);
	while (location)
	{
		strings = splitter(data, line, i, location);
		if (strings == NULL)
			return (-2);
		args_normalizer(strings, data);
		node = arglstnew(strings, '|');
		args_lstadd_back(&data->ar, node);
		i = location;
		location = i_inside_array(pars->ppl, pars->ppc, i, pars->next);
	}
	strings = splitter(data, line, i, pars->next);
	if (strings == NULL)
		return (-2);
	args_normalizer(strings, data);
	node = arglstnew(strings, 0);
	args_lstadd_back(&data->ar, node);
	return (0);
}

void args_normalizer(char **splits, t_data *data)
{
	int i;
	char *tmp;

	i = 0;
	while (splits[i] != NULL)
	{
		tmp = splits[i];
		splits[i] = ft_strtrim(splits[i], " |");
		free(tmp);
		if (splits[i] == NULL)
			ft_exit(-1, data, 1);
		if (splits[i][0] == '<' || splits[i][0] == '>')
		{
			tmp = splits[i];
			redirects_extractor(splits, i);
			free(tmp);
		}
		else
		{
			splits[i] = begin_env_replace(splits[i], data->envlist, data);
			splits[i] = quotes_worker(splits[i], data);
			splits[i] = trash_replacer(splits[i], data);
		}
		i++;
	}
}

char *quotes_worker(char *string, t_data *data)
{
	char q;

	q = get_dominator_quotes(string);
	if (q == '\'')
		return del_quotes(string, '\'', data);
	else if (q == '"')
		return del_quotes(string, '"', data);
	return (string);
}

char *begin_env_replace(char *string, t_list_env *envs, t_data *data)
{
	int sq;
	int dq;
	int i;
	char *tmp;

	sq = 0;
	dq = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (type_quotes(string, i) == '\'')
			sq++;
		if (type_quotes(string, i) == '"')
			dq++;
		if (string[i] == '$' && !(sq % 2) && ((string[i - 1] != '\\' && i) || \
				(!i)))
		{
			tmp = string;
			string = env_worker(string, i, envs, data);
			if (string == NULL)
				ft_exit(-1, data, 1);
			free(tmp);
		}
		i++;
	}
	return (string);
}

char type_quotes(char *string, int i)
{
	if ((!i && string[i] == '\'') || \
				(i && string[i] == '\'' && string[i - 1] != '\\'))
		return '\'';
	if ((!i && string[i] == '"') || \
				(i && string[i] == '"' && string[i - 1] != '\\'))
		return '"';
	return (0);
}