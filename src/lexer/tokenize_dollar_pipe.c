/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_dollar_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:41:17 by osajide           #+#    #+#             */
/*   Updated: 2023/05/31 17:51:51 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

void	if_dollar_sign(char *line, t_list **lst, int *pos)
{
	int		start;
	char	*temp;
	
	temp = NULL;
	start = *pos;
	(*pos)++;
	// while (line[*pos] && ((line[*pos] >= 'a' && line[*pos] <= 'z') || (line[*pos] >= 'A' && line[*pos] <= 'Z') || (line[*pos] >= '0' && line[*pos] <= '9')))
	// 	(*pos)++;
	while (line[*pos] && line[*pos] != ' ' && line[*pos] != '|' && line[*pos] != '<' && line[*pos] != '>')
	{
		if (line[*pos] == 34)
			skip_inside_quotes(line, pos, 34);
		else if (line[*pos] == 39)
			skip_inside_quotes(line, pos, 39);
		(*pos)++;
	}
	temp = ft_substr(line, start, *pos);
	ft_lstadd_back(lst, ft_lstnew(temp, NOTHING, ENV));
	(*pos)--;
}

void	if_pipe(char *line, t_list **lst, int *pos)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(temp , "|");
	ft_lstadd_back(lst, ft_lstnew(temp, NOTHING, PIPE));
}