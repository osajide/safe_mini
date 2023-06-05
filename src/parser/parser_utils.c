/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:11:53 by osajide           #+#    #+#             */
/*   Updated: 2023/06/05 18:15:02 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_redir	*new_redir_node(char *file, int type)
{
	t_redir *redir;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->file = file;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void	add_redir_node_back(t_redir **redir, t_redir *new_node)
{
	t_redir *tmp;

	if (!new_node)
		return ;
	if (!*redir)
	{
		*redir = new_node;
		return ;
	}
	tmp = *redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}