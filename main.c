#include "minishell.h"
#include "parseader.h"

int g_status = 0;
int g_lastpid = 0;
char g_echo_n = 0;


void close_2_fd(int *fd)
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

void	close_all_redir_fd(t_data *data)
{
	t_args *tmp;

	tmp = data->ar;
	while (tmp)
	{
		close_2_fd(tmp->file);
		/*
		if (tmp->file[0] >= 0)
			close(tmp->file[0]);
		if (tmp->file[1] >= 0)
			close(tmp->file[1]);
		 */
		tmp = tmp->next;
	}
}

void reset_fd(t_data *data, int *file_fd)
{
	//dup2(data->orig_fd[0], 0);
	//dup2(data->orig_fd[1], 1);
	close_2_fd(file_fd);
}

/*
** There is a need for close_all_redir_fd(), in case parser returns -1
** -> it means something might be fucked up while opening files.
** But maybe it is unnecessary - think about it
*/

static void renew_data(t_data *data)
{
	close_all_redir_fd(data);
	args_clearlist(&data->ar);
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
		ft_exit(127, data, 0);
	}
	data->envlist = get_envlist(env);
	data->orig_fd[0] = dup(0);
	data->orig_fd[1] = dup(1);
	data->pipe_fd[0] = 0;
	data->pipe_fd[1] = 0;
	data->envp = NULL;
	data->add_to_prompt = NULL;
}

static void process_and_clear(char *line, t_data *data)
{
	execution(data);
	renew_data(data);
}

/*
** i = begin(line, 0, &data);
** while (1 <= i)
** {
**		i = begin_parser(line, i+1, &data);
** }
*/

void minishell(t_data *data)
{
	char *line;
	int ret;

	//line = "echo > liza liza | echo batya > batya";
	while ((line = ft_readline(data)) != NULL)
	{
		if (g_echo_n == 1)
		{
			g_echo_n = 0;
			if (data->add_to_prompt != NULL)
				ft_free((void **)&data->add_to_prompt);
		}
		if (line[0] != '\0')
		{
			ret = begin_parser(line, 0, data);
			//debug parser
			//printf("argslist size %d\n", argslstsize(data->ar));
			//end debug
			if (ret == -1)
			{
				renew_data(data); // TODO: нужно, потому что может ошибка какая-то при открытии файлов, но нужно ли фришить аргументы или просто закрыть файлы редиректов?
				continue ;
			}
			if (ret == -2)
			{
				renew_data(data); // TODO: нужно, потому что может ошибка какая-то при открытии файлов, но нужно ли фришить аргументы или просто закрыть файлы редиректов?
				continue ;
			}
			process_and_clear(line, data);
			while (ret > 0)
			{
				//ret = test_parser(line + count, count, data); // TODO: строку сначала давай в парсер виталика, а не line+count
				
				ret = begin_parser(line, ret + 1, data);
				//debug parser
				//printf("argslist size %d\n", argslstsize(data->ar));
				//end debug
				if (ret == -2)
				{
					renew_data(data); // TODO: нужно, потому что может ошибка какая-то при открытии файлов, но нужно ли фришить аргументы или просто закрыть файлы редиректов?
					break ;
				}


				process_and_clear(line, data);
			}
		}
		free(line);
	}
}

int			main(int argc, char **argv, char **env)
{
	t_data	data;

	init_shell(&data, argc, argv, env);
	load_history(&data);
	set_signals(&data);
	minishell(&data);

	return (0);
}
