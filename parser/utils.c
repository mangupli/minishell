#include "minishell.h"
#include "parseader.h"

bool i_inside_array(int *array, int count, int i, int next)
{
	int j;

	j = 0;
	while (j < count)
	{
		if (array[j] > i && array[j] < next)
			return (True);
		j++;
	}
	return (False);
}