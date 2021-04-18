#include "minishell.h"

static char skip_flag_n(char **args, int *i)
{
	char ret;

	ret = 0;
	while (!ft_strcmp(args[*i], "-n"))
	{
		(*i)++;
		ret = 1;
		if (args[*i] == NULL)
			break;
	}
	return (ret);
}



static void print_echo_n(t_data *data, char **args, int i)
{
	g_echo_n = 1;
	//handle_args(data, args, i - 1);
	ft_putstr_fd(data->add_to_prompt, 1);
}

void 	shell_echo(t_data *data, char **args)
{
	char flag;
	int i;

	g_status = 0;
	if (args)
	{
		if (!args[1])
		{
			ft_putstr_fd("\n", 1);
			return ;
		}
		i = 1;
		flag = skip_flag_n(args, &i);
		if (!flag)
		{
			while (args[i])
			{
				ft_putstr_fd(args[i], 1);
				if (args[i + 1] != NULL)
					ft_putstr_fd(" ", 1);
				i++;
			}
			ft_putstr_fd("\n", 1);
		}
	}
	g_status = 0;
}
