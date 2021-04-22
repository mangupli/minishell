#include "minishell.h"
#include "parseader.h"

int i_inside_array(int *array, int count, int i, int next)
{
	int j;

	j = 0;
	while (j < count)
	{
		if (array[j] > i && array[j] < next)
			return (array[j]);
		j++;
	}
	return (0);
}

int splits_count(int *array, int array_el_count, int i, int next)
{
	int j;
	int count;

	j = 0;
	count = 0;
	while (j < array_el_count && array[j] < next)
	{
		if (array[j] > i && array[j] < next)
			count++;
		j++;
	}
	return (count + 2);
}

char *slash_replacer(char *string)
{
	char *new_string;
	int i;
	int j;
	int f;

	new_string = (char *)malloc(ft_strlen(string)); //TODO MALLOCS
	i = 0;
	j = 0;
	f = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\\' && !f)
		{
			i++;
			f++;
		}
		new_string[j] = string[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
	return (new_string);
}
