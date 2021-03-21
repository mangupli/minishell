/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:04:35 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/04 20:05:54 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	if (str)
	{
		len = ft_strlen(str);
		while (len - 1 > i)
		{
			tmp = str[i];
			str[i] = str[len - 1];
			str[len - 1] = tmp;
			len--;
			i++;
		}
	}
	return (str);
}
