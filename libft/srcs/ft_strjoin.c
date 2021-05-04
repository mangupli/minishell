/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:40:15 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/19 17:19:18 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	total;

	if (!s1)
		s1 = "\0";
	if (!s2)
		s2 = "\0";
	total = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (total + 1));
	if (dst != NULL)
	{
		ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
		ft_strlcat(dst, s2, total + 1);
	}
	return (dst);
}
