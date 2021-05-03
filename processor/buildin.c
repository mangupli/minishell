#include "minishell.h"

int	func_in_return(t_data *data, char **args, void (*f)(t_data *, char **))
{
	f(data, args);
	return (1);
}

int	exec_my_function(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		if (argslstsize(data->ar) > 1)
			return (1);
		return (shell_exit(args, 0, data));
	}
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, args, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, args, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, args, shell_unset));
	args[0] = ft_str_to_lower(args[0]);
	if (!ft_strcmp(args[0], "echo"))
		return (func_in_return(data, args, shell_echo));
	else if (!ft_strcmp(args[0], "pwd"))
		return (func_in_return(data, args, shell_pwd));
	else if (!ft_strcmp(args[0], "env"))
		return (func_in_return(data, args, shell_env));
	return (0);
}

int	first_my_function(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		if (argslstsize(data->ar) > 1)
			return (1);
		return (shell_exit(args, 0, data));
	}
	else if (!ft_strcmp(args[0], "cd"))
		return (func_in_return(data, args, shell_cd));
	else if (!ft_strcmp(args[0], "export"))
		return (func_in_return(data, args, shell_export));
	else if (!ft_strcmp(args[0], "unset"))
		return (func_in_return(data, args, shell_unset));
	return (0);
}
