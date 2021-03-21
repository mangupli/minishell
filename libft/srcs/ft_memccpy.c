/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 00:25:02 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/10 15:06:36 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n-- && (dst || src))
	{
		*((unsigned char*)dst) = *((unsigned char*)src++);
		if (*(unsigned char*)(dst++) == (unsigned char)c)
			return (dst);
	}
	return (NULL);
}
