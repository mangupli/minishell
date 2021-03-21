/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:59:06 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/07 17:04:59 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	if (n != 0)
		dest[i] = '\0';
	return (dest);
}
