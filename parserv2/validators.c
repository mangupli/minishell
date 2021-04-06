#include "minishell.h"
#include "parseader.h"

int quotes_validator(char *line)
{
	int		i;
	int		double_quotes;
	int		single_quotes;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' && i > 0 && line[i - 1] != '\\') || \
				(!i && line[i] == '\''))
			single_quotes++;
		if ((line[i] == '"' && i > 0 && line[i - 1] != '\\') || \
				(!i && line[i] == '"'))
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 || double_quotes % 2)
	{
		display_error("minishell", "syntax error", "unexpected token");
		return (-1);
	}
	return (0);
}

int ft_strlen_to_pipe_or_comma(char *line, int i)
{
	int len;

	len = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '|' || line[i] == ';') && i > 0 && line[i - 1] != '\\')
			break ;
		i++;
		len++;
	}
	return (len);
}



int		is_end_arg(char *line, int i, int double_quotes, int single_quotes)
{
	if ((line[i] == '|' || line[i] == ';') && i > 0 && \
			line[i - 1] != '\\' && ft_strlen(line) - 1 > i && \
			!(double_quotes % 2) && !(single_quotes % 2))
		return (1);
	return (0);
}

int		is_end_line(char *line, int i)
{
	while (line[i] != '\0')
	{
		if ((line[i] == '|' || line[i] == ';') && i > 0 && line[i - 1] != '\\')
			return (0);
		i++;
	}
	return (1);
}



int	twinks_validator(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\0')
	{
		if ((line[i] == '|' && i + 1 <= len && line[i + 1] == '|') || \
			(line[i] == ';' && i + 1 <= len && line[i + 1] == ';') || \
			(i + 2 <= len && line[i] == '>' && line[i + 1] == '>' && \
			line[i + 2] == '>') || (line[i] == '<' && i + 1 <= len && \
			line[i + 1] == '<') || (line[i] == '|' && i == 0))
		{
			if ((i > 0 && line[i - 1] != '\\') || (i == 0))
			{
				display_error("minishell", "syntax error", "unexpected token");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
