#include "minishell.h"
#include "parseader.h"

/*
int		g_struct.status = 0;
char	g_echo_n = 0;
*/

static void	init_shell(t_data *data, int argc, char **argv, char **env)
{
	data->prompt = "superbash> ";
	data->hist.len = 0;
	data->hist.list = NULL;
	data->hist.maxlen = HISTORY_MAX_LEN;
	if (argc != 1)
	{
		display_error("minishell", argv[1], "cannot execute this file");
		ft_exit(127, data, 0);
	}
	data->envlist = get_envlist(env);
	data->orig_fd[0] = dup(0);
	data->orig_fd[1] = dup(1);
	data->pipe_fd[0] = 0;
	data->pipe_fd[1] = 0;
	data->envp = NULL;
	data->add_to_prompt = NULL;
	g_struct.echo_n = 0;
	g_struct.status = 0;
}

static void	process_and_clear(t_data *data)
{
	execution(data);
	renew_data(data);
}

static int	core_minishell(t_data *data, char *line)
{
	int	ret;

	ret = begin_parser(line, 0, data);
	if (ret == -1 || ret == -2)
	{
		renew_data(data);
		return (-1);
	}
	process_and_clear(data);
	while (ret > 0)
	{
		ret = begin_parser(line, ret + 1, data);
		if (ret == -2)
		{
			renew_data(data);
			return (-1);
		}
		process_and_clear(data);
	}
	return (0);
}

void	minishell(t_data *data)
{
	char	*line;

	//line = getenv("to_test");
	line = ft_readline(data);
	while (line != NULL)
	{
		if (g_struct.echo_n == 1)
		{
			g_struct.echo_n = 0;
			if (data->add_to_prompt != NULL)
				ft_free((void **)&data->add_to_prompt);
		}
		if (line[0] != '\0')
		{
			core_minishell(data, line);
		}
		free(line);
		line = ft_readline(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_shell(&data, argc, argv, env);
	load_history(&data);
	set_signals(&data);
	minishell(&data);
	return (0);
}
