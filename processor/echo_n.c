#include "minishell.h"

static char	*handle_args(char **args, int i)
{
	char	*string;
	char	*tmp;

	string = NULL;
	tmp = NULL;
	while (args[i])
	{
		if (args[i + 1] != NULL)
		{
			tmp = ft_strjoin(string, args[i]);
			if (string != NULL)
				ft_free((void **)&string);
			string = ft_strjoin(tmp, " ");
			ft_free((void **)&tmp);
		}
		else
		{
			tmp = ft_strjoin(string, args[i]);
			if (string != NULL)
				ft_free((void **)&string);
			string = tmp;
		}
		i++;
	}
	return (string);
}

void	skip_n(t_data *data, t_args *tmp)
{
	int	i;

	if ((!ft_strcmp(tmp->args[1], "-n")))
	{
		g_struct.echo_n = 1;
		i = 0;
		while (!ft_strcmp(tmp->args[++i], "-n"))
		{
			if (tmp->args[i + 1] == NULL)
				return ;
		}
		if (data->add_to_prompt != NULL)
			ft_free((void **)&data->add_to_prompt);
		data->add_to_prompt = handle_args(tmp->args, i);
	}
}

void	find_echo_n(t_data *data)
{
	t_args	*tmp;

	tmp = data->ar;
	while (tmp)
	{
		if (!ft_strcmp(tmp->args[0], "echo"))
		{
			if (!tmp->args[1])
			{
				tmp = tmp->next;
				continue ;
			}
			skip_n(data, tmp);
		}
		tmp = tmp->next;
	}
}
