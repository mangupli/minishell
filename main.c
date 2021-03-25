#include "minishell.h"
#include "includes/parseader.h"

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
}

int			main(int argc, char **argv, char **env)
{
	char *line;
	t_data	data;

	init_shell(&data, argc, argv, env);
	while ((line = ft_readline(&data)) != NULL)
	{
		if (line[0] != '\0')
		{
			if (ultimate_validator(line) == 0)
			{

				data.args = ft_split(line, ' ');
				execution(&data);
				add_history(line, &data.hist); /* Add to the list. */
				save_history("list.txt"); /* Save the list on disk. */
			}
		}
		free(line);
	}
	return (0);
}
