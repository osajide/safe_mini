/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:33:01 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 18:17:58 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"
#include "../inc/expander.h"
#include "../inc/execution.h"
#include <stdio.h>
#include <stdlib.h>

t_general	general;

void	clear_lst(t_list *lst)
{
	t_list	*cur;
	
	if (!lst)
		return ;
	while (lst)
	{
		cur  = lst;
		lst = lst->next;
		free(cur);
	}
}

void	print_linked_list(t_list *lst)
{
	t_list	*t;

	t = lst;
	while (t)
	{
		printf("\n\n\n-----------------------------\n");
		printf("t->content = %s\n", t->data->content);
		if (t->data->token == 1)
			printf("t->token = WORD\n");
		else if (t->data->token == 2)
			printf("t->token = ENV\n");
		else if (t->data->token == 3)
			printf("t->token = WHITE_SPACE\n");
		else if (t->data->token == 4)
			printf("t->token = SINGLE_Q\n");
		else if (t->data->token == 5)
			printf("t->token = DOUBLE_Q\n");
		else if (t->data->token == 6)
			printf("t->token = PIPE\n");
		else if (t->data->token == 7)
			printf("t->token = REDIR_IN\n");
		else if (t->data->token == 8)
			printf("t->token = REDIR_OUT\n");
		else if (t->data->token == 9)
			printf("t->token = APPEND_REDIR\n");
		else if (t->data->token == 10)
			printf("t->token = HEREDOC\n");
		t = t->next;
	}
}

void	minishell(char **env)
{
	char	*line;
	t_list	*lst;
	t_cmd	*cmd;
	int		cmd_count;

	lst = NULL;
	while (1)
	{
		line = display_prompt();
		if(line && line[0])
		{	
			if (check_quotes(line, &general))
			{
				loop_on_input(line, &lst);
				if (lst)
				{
					if (!analyzer(lst, &general))
					{
						// print_linked_list(lst);
						cmd = fill_struct_cmd(lst, &general.nbr_cmd);
						cmd = expander(cmd, &general, env);
						if(cmd)
							execute_multiple_cmd(cmd, &general, env);
					}
				}
			}
			free(line);
			clear_lst(lst);
			lst  = NULL;
		}
	}
}
