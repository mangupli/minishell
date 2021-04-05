#include "minishell.h"

static void renew_data(t_data *data)
{
	//free args

	/*
	while (data->ar)
	{
		if (data->ar->args)
		{
			free_2d_array(data->ar->args);
			data->ar->args = (char **)ft_calloc(1, sizeof(char **));
		}
		data->ar->type = 0;
		data->ar = data->ar->next;
	}
	 */

	args_clearlist(&data->ar);

	//do we need to reset original fd?
	dup2(data->orig_fd[0], 0);
	dup2(data->orig_fd[1], 1);
}

static void init_shell(t_data *data, int argc, char **argv, char **env)
{
	data->prompt = "superbash> ";
	data->hist.len = 0;
	data->hist.list = NULL;
	data->hist.maxlen = HISTORY_MAX_LEN;
	data->echo = NULL;
	data->func.echo_n = 0;
	if (argc != 1)
	{
		display_error("minishell", argv[1], "cannot execute this file");
		ft_exit(1);
	}
	data->envlist = get_envlist(env);
	data->orig_fd[0] = dup(0);
	data->orig_fd[1] = dup(1);
	data->file[0] = -1;
	data->file[1] = -1;
}

int			main(int argc, char **argv, char **env)
{
	char *line;
	t_data	data;
	int i;
	int count;

	init_shell(&data, argc, argv, env);

	//line = "pwd ; echo liza; ls -la";
	while ((line = ft_readline(&data)) != NULL)
	{
		if (line[0] != '\0')
		{

			count = 0;
			while (*(line + count))
			{
				count += test_parser(line + count, count, &data); // строку сначала давай в парсер виталика, а не line+count
				printf("count %d\n", count);

				add_history(line, &data.hist); // Add to the list.
				save_history("list.txt"); // Save the list on disk.

				if (count == -1)
				{
					// renew_data(&data); // нужно ли?
					break;
				}
				else
					execution(&data);

				renew_data(&data);
			}
		}
		free(line);
	}
	return (0);
}
