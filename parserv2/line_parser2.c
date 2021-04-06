//
// Created by Moaning Stonehouse on 3/28/21.
//

#include "minishell.h"
#include "parseader.h"

char **new_split(char *str)
{
	char **strs;
	int count;
	int i;
	int j;

	count = count_args(str);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		strs[j] = (char *)malloc(ft_strlen_to_space(str, i) + 1);
		i = str_fill(str, strs[j], i);
		j++;
	}
	strs[j] = NULL;
	return (strs);
}

int str_fill(char *str, char *dest, int i)
{
	int		double_quotes;
	int		single_quotes;
	int		j;

	double_quotes = 0;
	single_quotes = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_quotes++;
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == ' ' && single_quotes % 2 && double_quotes % 2 && \
            i > 0 && str[i - 1] != '\\')
		{
			dest[j] = '\0';
			return (i);
		}
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (i);
}

int ft_strlen_to_space(char *str, int i)
{
	int len;
	int		double_quotes;
	int		single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_quotes++;
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == ' ' && single_quotes % 2 && double_quotes % 2 && \
			i > 0 && str[i - 1] != '\\')
			return (len);
		i++;
		len++;
	}
	return (len);
}

void	get_type(char c, t_args *args)
{
	if (c == '|')
	{
		args->type = '|';
		return ;
	}
	if (c == ';')
	{
		args->type = ';';
		return ;
	}
	args->type = 0;
}
