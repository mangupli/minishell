/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:49:07 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/05 16:55:57 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_str_to_lower(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isupper(str[i]))
				str[i] = ft_tolower(str[i]);
			i++;
		}
	}
	return (str);
}
