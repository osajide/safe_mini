/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:33:54 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/01 16:28:03 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*temp;

	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = node;
	node->prev = temp;
	node->next = NULL;
}
