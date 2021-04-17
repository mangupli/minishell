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