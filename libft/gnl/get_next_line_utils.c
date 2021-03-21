/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:45:13 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/19 17:48:53 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (s[i] == '\0' ? NULL : &s[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	total;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (total + 1));
	if (NULL == dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		dest[len] = s1[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}
