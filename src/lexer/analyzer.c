/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:10 by osajide           #+#    #+#             */
/*   Updated: 2023/06/02 20:03:57 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	analyzer(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->data->token == PIPE)
		{
			if (!temp->prev || !temp->next || temp->next->data->token == PIPE)
				return (ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2), 1);
		}
		else if (temp->data->token == REDIR_OUT || temp->data->token == APPEND_REDIR)
		{
			if (!temp->next || (temp->next->data->token != WORD && temp->next->data->token != ENV))
				return (ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2), 1);
		}
		else if (temp->data->token == REDIR_IN || temp->data->token == HEREDOC)
		{
			if (!temp->next || (temp->next->data->token != WORD && temp->next->data->token != ENV))
				return (ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2), 1);
		}
		temp = temp->next;
	}
	return (0);
}
