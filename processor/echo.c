#include "minishell.h"

static char	skip_flag_n(char **args, int *i)
{
	char	ret;

	ret = 0;
	while (!ft_strcmp(args[*i], "-n"))
	{
		(*i)++;
		ret = 1;
		if (args[*i] == NULL)
			break ;
	}
	return (ret);
}

static void	print_args(char **args, int i)
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

void	shell_echo(t_data *data, char **args)
{
	char	flag;
	int		i;

	(void)data;
	g_struct.status = 0;
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
			print_args(args, i);
	}
	g_struct.status = 0;
}
