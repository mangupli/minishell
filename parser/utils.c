#include "minishell.h"
#include "parseader.h"

int	i_inside_array(int *array, int count, int i, int next)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (array[j] > i && array[j] < next)
			return (array[j]);
		j++;
	}
	return (0);
}

int	splits_count(int *array, int array_el_count, int i, int next)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (j < array_el_count && array[j] < next)
	{
		if (array[j] > i && array[j] < next)
			count++;
		j++;
	}
	return (count + 2);
}

char	*slash_replacer(char *string, t_data *data)
{
	char	*new_string;
	int		i;
	int		j;
	int		f;

	new_string = (char *)malloc(ft_strlen(string));
	if (new_string == NULL)
		ft_exit(-1, data, 1);
	i = 0;
	j = 0;
	f = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\\' && !f)
		{
			i++;
			f++;
		}
		new_string[j] = string[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
	return (new_string);
}

void	freedom(t_par *pars)
{
	free(pars->dql);
	free(pars->sql);
	free(pars->ppl);
	free(pars->sccl);
	free(pars->rl);
	free(pars->rrl);
	free(pars->sl);
	free(pars->locs);
	free(pars->line_copy);
}

bool	opener_begin(t_data *data)
{
	if (data->pars.redirs)
	{
		if (file_opener(data->pars.redirs, data, arglstlast(data->ar)) == -2)
			return (true);
		ft_free((void **)&data->pars.redirs);
	}
	return (false);
}
