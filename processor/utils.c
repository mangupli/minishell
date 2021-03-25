#include "minishell.h"
#include "parseader.h"

int check_symbols(char *name, char *content)
{
	int i;

	if (!ft_isalpha(name[0]))
		return (1);
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
	}
	return (0);
}