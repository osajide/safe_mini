/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:10 by osajide           #+#    #+#             */
/*   Updated: 2023/06/01 16:39:13 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	analyzer(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	// while (temp)
	// {
	// 	printf("%s->", temp->data->content);
	// 	temp = temp->next;
	// }
	// printf("\n");
	while (temp)
	{
		if (temp->data->token == PIPE)
		{
			if (!temp->next || temp->next->data->token != WORD || temp->prev->data->token == PIPE)
				printf("!!!!!!!!!!!!!!!!!!!!!!! Error !!!!!\n");
		}
		temp = temp->next;
	}
}