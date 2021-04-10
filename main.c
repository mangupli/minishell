#include "minishell.h"

int g_status = 0;
int g_lastpid = 0;

void	close_file_fd(t_data *data)
{
	if (data->file[0] >= 0)
		close(data->file[0]);
	if (data->file[1] >= 0)
		close(data->file[1]);
}


void reset_fd(t_data *data)
{
	//do we need to reset original fd?
	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
	close_file_fd(data);
	data->file[1] = -1;
	data->file[0] = -1;
}

static void renew_data(t_data *data)
{
	//free args
	args_clearlist(&data->ar);

	reset_fd(data);
}

static void init_shell(t_data *data, int argc, char **argv, char **env)
{
	data->prompt = "superbash> ";
	data->hist.len = 0;
	data->hist.list = NULL;
	data->hist.maxlen = HISTORY_MAX_LEN;
	if (argc != 1)
	{
		display_error("minishell", argv[1], "cannot execute this file");
		ft_exit(127, data);
	}
	data->envlist = get_envlist(env);
	data->orig_fd[0] = dup(0);
	data->orig_fd[1] = dup(1);
	data->file[0] = -1;
	data->file[1] = -1;
	data->envp = NULL;
}

void minishell(t_data *data)
{
	char *line;
	int count;

	//line = "echo $?";
	while ((line = ft_readline(data)) != NULL)
	{
		if (line[0] != '\0')
		{
			count = 0;
			while (*(line + count))
			{
				count += test_parser(line + count, count, data); // строку сначала давай в парсер виталика, а не line+count

				add_history(line, &data->hist); // Add to the list.
				save_history("list.txt"); // Save the list on disk.

				if (count == -1)
				{
					// renew_data(&data); // нужно ли?
					break;
				}
				else
					execution(data);
				renew_data(data);
			}
		}
		free(line);
	}
}

int			main(int argc, char **argv, char **env)
{
	t_data	data;

	init_shell(&data, argc, argv, env);
	set_signals(&data);
	minishell(&data);

	return (0);
}
