//
// Created by Moaning Stonehouse on 3/30/21.
//

#include "minishell.h"
#include "parseheaderv2.h"

bool behind_has_backslash(char *line, char current, char needed, int i)
{
	if (current == needed && ((i > 0 && line[i - 1] != '\\') || !i))
		return (False);
	return (True);
}

bool im_in_quotes(int i, int count, int *locations)
{
	int j;

	j = 0;
	while (j < count)
	{
		if (i < locations[j])
			break ;
		j++;
	}
	return (j % 2);
}

bool im_in_end_or_begin(char *line, char needed)
{
	int len;

	len = ft_strlen(line);
	if ((line[len - 1] == needed && len > 2 && line[len - 2] != '\\') || \
			(line[0] == needed))
		return (True);
	return (False);
}