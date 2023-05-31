/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:10:49 by osajide           #+#    #+#             */
/*   Updated: 2023/05/31 17:54:06 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>


void	loop_on_input(char *line, t_list **lst)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == 32)
			i++;
		if ((line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9'))
		{
			printf("if_string begin\n");
			if_string(line, lst, &i);
			printf("if_string done\n");
		}
		else if (line[i] == 39)
		{
			printf("if_single_quotes begin\n");
			if_single_quote(line, lst, &i);
			printf("if_single_quotes done\n");
		}
		else if (line[i] == 34)
		{
			printf("if_double_quotes begin\n");
			if_double_quote(line, lst, &i);
			printf("if_double_quotes done\n");
		}
		else if (line[i] == '$')
		{
			printf("if_dollar_sign begin\n");
			if_dollar_sign(line, lst, &i);
			printf("if_dollar_sign done\n");
		}
		else if (line[i] == '|')
		{
			printf("if_pipe begin\n");
			if_pipe(line, lst, &i);
			printf("if_pipe done\n");
		}
		else if (line[i] == '<')
		{
			printf("if_redir begin\n");
			input_redirection(line, lst, &i);
			printf("if_redir done\n");
		}
		else if (line[i] == '>')
		{
			printf("if_redir begin\n");
			output_redirection(line, lst, &i);
			printf("if_redir done\n");
		}
		else
		{
			printf("other_characters begin\n");
			other_characters(line, lst, &i);
			printf("other_characters done\n");
		}
		i++;
	}
}
