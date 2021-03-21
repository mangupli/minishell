/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:11:54 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/02 23:06:27 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*dst;
	size_t			i;
	size_t			total;

	total = count * size;
	dst = malloc(total);
	if (NULL == dst)
		return (NULL);
	i = 0;
	while (i < total)
	{
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}
