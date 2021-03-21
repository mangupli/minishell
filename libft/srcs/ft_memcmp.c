/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:17:37 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/02 20:24:23 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = s1;
	p2 = s2;
	if (n != 0)
	{
		while (n != 0)
		{
			if (*p1++ != *p2++)
				return (*--p1 - *--p2);
			n--;
		}
	}
	return (0);
}
