//
// Created by Moaning Stonehouse on 3/21/21.
//

#include "minishell.h"
#include "parseader.h"

t_args *line_parser(char *line)
{
	t_args	*args;

	if (quotes_validator(line) == -1 || twinks_validator(line) == -1)
		return (NULL);
	args = (t_args *)malloc(sizeof(t_args) * (get_count(line) + 1));
	args_fill(line, args);
	return (args);
}

int get_count(char *line)
{
	int		i;
	int		double_quotes;
	int		single_quotes;
	int		count;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	count = 1;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			double_quotes++;
		if (line[i] == '\'')
			single_quotes++;
		if (is_end_arg(line, i, double_quotes, single_quotes))
			count++;
		i++;
	}
	return (count);
}

void	args_fill(char *line, t_args *args)
{
	int		i;
	int		j;
	int		start;
	int		double_quotes;
	int		single_quotes;

	i = 0;
	j = 0;
	double_quotes = 0;
	single_quotes = 0;
	start = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			double_quotes++;
		if (line[i] == '\'')
			single_quotes++;
		if (is_end_arg(line, i, double_quotes, single_quotes))
		{
			get_type(line[i], &args[j]);
			get_string(line, start, i, &args[j]);
			start = i + 1;
			j++;
		}
		i++;
		if (is_end_line(line, i))
		{
			get_string(line, start, ft_strlen(line), &args[j]);
			j++;
			break ;
		}
	}
	args[j].args = NULL;
}

int	get_string(char *line, char start, char stop, t_args *args)
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen_to_pipe_or_comma(line, start));
	i = 0;
	while (start < stop)
	{
		str[i] = line[start];
		i++;
		start++;
	}
	str[i] = '\0';
	args->args = new_split(str);
	free(str);
	return (i);
}

int	count_args(char *str)
{
	int 	i;
	int 	count;
	int		double_quotes;
	int		single_quotes;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	count = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_quotes++;
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == ' ' && !(single_quotes % 2) && !(double_quotes % 2) && \
			i > 0 && str[i - 1] != '\\')
			count++;
		i++;
	}
	return (count);
}
