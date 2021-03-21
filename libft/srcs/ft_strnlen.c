/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:49:01 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/10 19:29:36 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strnlen(const char *s, size_t max)
{
	size_t len;

	len = 0;
	while (s[len] && len < max)
		len++;
	return (len);
}
