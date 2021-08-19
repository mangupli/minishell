/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:41:15 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/12 16:35:02 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_cntstr(char const *s, char c)
{
	unsigned int	i;
	int				n;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static void	ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static char	**ft_allocate(char **new, const char *s, char c, int i)
{
	int	k;
	int	start;

	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			new[k] = ft_strndup(s + start, i - start);
			if (new[k] == NULL)
			{
				ft_free(new, k);
				return (NULL);
			}
			k++;
		}
	}
	new[k] = NULL;
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;

	if (s == NULL)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_cntstr(s, c) + 1));
	if (NULL == new)
		return (NULL);
	i = 0;
	return (ft_allocate(new, s, c, i));
}
