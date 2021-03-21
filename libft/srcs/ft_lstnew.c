/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:54:47 by mspyke            #+#    #+#             */
/*   Updated: 2020/11/08 21:05:36 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list) * 1);
	if (NULL == new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
