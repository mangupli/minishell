/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 00:16:37 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/03 22:42:33 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned const char *s;
	unsigned char		*d;
	size_t				c;

	c = 0;
	s = src;
	d = dst;
	while (c < n)
	{
		d[c] = s[c];
		c++;
	}
	return (dst);
}
