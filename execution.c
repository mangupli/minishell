#include "minishell.h"

int 	execution(char *line, char **env)
{
	pid_t pid;
	int status;
	char **args;
	args = ft_split(line, ' ');
	pid = fork();
	if (pid == 0) // child
	{
		if (!ft_strcmp(args[0], "echo"))
			shell_echo(args);
		execve(line, args, 0);
	}
	else //parent
	{
		waitpid(-1, &status, 0);
		//exit(status);
	}
	return (0);
}