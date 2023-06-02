/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:10 by osajide           #+#    #+#             */
/*   Updated: 2023/06/02 17:15:43 by osajide          ###   ########.fr       */
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
			if (!temp->prev || !temp->next ||( temp->next->data->token != WORD &&  temp->next->data->token != ENV))
			{
				// printf("\n\n\nminishell: syntax error !!!!\n\n\n");
				ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2);
				return ;
			}
		}
		else if (temp->data->token == REDIR_OUT || temp->data->token == APPEND_REDIR)
		{
			if (!temp->next || temp->next->data->token != WORD)
			{
				// if (temp->next && temp->next->data->token == PIPE)
				// 	printf("\n\n\nminishell: syntax error near unexpected token `|'\n\n\n");
				// else
					// printf("\n\n\nminishell: syntax error !!!!\n\n\n");
				ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2);
				return ;
			}
		}
		temp = temp->next;
	}
}