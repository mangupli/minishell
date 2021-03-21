/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 23:06:44 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/02 23:26:47 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
