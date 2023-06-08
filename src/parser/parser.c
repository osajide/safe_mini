/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:46:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/08 19:37:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

int	command_number(t_list *lst)
{
	int	command_counter;

	command_counter = 1;
	while (lst)
	{
		if (lst->data->token == PIPE)
			command_counter++;
		lst = lst->next;
	}
	return (command_counter);
}

char	*get_command(t_list *lst, int *pos)
{
	while (lst && lst->data->token != PIPE)
	{
		if (lst->data->token != WORD && lst->data->token != ENV)
		{
			lst = lst->next->next;
			(*pos)++;
			(*pos)++;
		}
		if (lst && (lst->data->token == WORD || lst->data->token == ENV))
			return (lst->data->content);
	}
	return (NULL);
}

t_args	*get_arg(t_list *lst, int *pos)
{
	t_args	*args;
	int		i;
	int		len;
	t_list	*tmp;
	t_args	*tmp_args;
	
	args = NULL;
	i = -1;
	while ((++i <= (*pos)) && lst)
		lst = lst->next;
	tmp = lst;
	while (lst && (lst->data->token == WORD || lst->data->token == ENV))
	{
		add_args_node_back(&args, new_args_node(lst->data->content));
		lst = lst->next;
	}
	return (args);
}

t_redir	*fill_struct_redir(t_list *lst)
{
	t_redir	*redir;

	redir = NULL;
	while (lst && lst->data->token != PIPE)
	{
		if (lst->data->token != WORD && lst->data->token != ENV)
		{
			lst = lst->next;
			if (lst && (lst->data->token == WORD || lst->data->token == ENV))
				add_redir_node_back(&redir, new_redir_node(lst->data->content, lst->prev->data->token));
		}
		lst = lst->next;
	}
	return (redir);
}

void	print_parser(t_cmd *cmd, int count_cmd)
{
	int i;
	int j;
	t_args *tmp_args;

	i = -1;
	tmp_args = cmd->args;
	while (++i < count_cmd)
	{
		if (cmd[i].command)
		{
			printf("\n******** COMMAND [%d]**************\n\n", i + 1);
			printf("\tcommand  = %s\n", cmd[i].command);
			j = -1;
			while (tmp_args)
			{
				printf("\t\033[1;32margument =\033[0m %s\n", tmp_args->argument);
				tmp_args = tmp_args->next;
			}
		}
		if (cmd[i].redir)
		{
			printf("\n******** REDIRECTION [%d]**************\n\n", i + 1);
			while(cmd[i].redir)
			{
				printf("\tfile == %s\n", cmd[i].redir->file);
				if (cmd[i].redir->type == REDIR_IN)
					printf("\ttype == %s\n", "REDIR_IN\n");
				else if (cmd[i].redir->type == REDIR_OUT)
					printf("\ttype == %s\n", "REDIR_OUT\n");
				else if (cmd[i].redir->type == HEREDOC)
					printf("\ttype == %s\n", "HEREDOC\n");
				else if (cmd[i].redir->type == APPEND_REDIR)
					printf("\ttype == %s\n", "APPEND_REDIR\n");
				cmd[i].redir = cmd[i].redir->next;
			}
		}
	}
}

t_cmd	*fill_struct_cmd(t_list *lst, int *cmd_count)
{
	t_cmd	*cmd;
	int		i;
	int		pos;
	
	*cmd_count = command_number(lst);
	cmd = malloc(*cmd_count * sizeof(t_cmd));
	pos = 0;
	i = 0;
	while (i < *cmd_count)
	{
		cmd[i].command = get_command(lst, &pos);
		cmd[i].args = get_arg(lst, &pos);
		// printf("\n\n\n\n\n\n\n\n\n ------>>>>>> cmd[%d].command->args->argument = %s\n\n\n\n\n\n\n\n\n", i, cmd[i].command->args->argument);
		cmd[i].redir = fill_struct_redir(lst);
		i++;
		while (lst && lst->data->token != PIPE)
			lst = lst->next;
		if (lst && lst->data->token == PIPE)
			lst = lst->next;
		pos = 0;
	}
	print_parser(cmd, *cmd_count);
	return (cmd);
}
