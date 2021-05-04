/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:48:15 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/08 17:51:40 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_cntnmb(int n)
{
	size_t	digits;

	digits = 0;
	if (n < 0)
		digits++;
	while (n / 10 != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits + 1);
}

static void	ft_locate_chars(char *start, char *ptr, int n)
{
	while (ptr >= start)
	{
		*ptr = n % 10 + '0';
		n /= 10;
		ptr--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_cntnmb(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		ft_locate_chars(str + 1, str + len - 1, 0 - n);
		str[len] = '\0';
	}
	else
	{
		ft_locate_chars(str, str + len - 1, n);
		str[len] = '\0';
	}
	return (str);
}
