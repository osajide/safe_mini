/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:46:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/05 18:40:46 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

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
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->data->token == WORD)
			return (temp->data->content);
		temp = temp->next;
		(*pos)++;
	}
	return (NULL);
}

char	**get_arg(t_list *lst, int *pos)
{
	char	**arg;
	int		i;
	int		len;
	t_list	*tmp;
	
	i = -1;
	while ((++i <= (*pos)) && lst)
		lst = lst->next;
	tmp = lst;
	len = 0;
	while (tmp && (tmp->data->token == WORD || tmp->data->token == ENV))
	{
		len++;
		tmp = tmp->next;
	}
	arg = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (lst && (lst->data->token == WORD || lst->data->token == ENV))
	{
		arg[i++] = lst->data->content;
		lst = lst->next;
	}
	arg[i] = NULL;
	return (arg);
}

t_command	*fill_struct_command(t_list *lst, int *pos)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = get_command(lst, pos);
	command->arg = get_arg(lst, pos);
	return (command);
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

	i = -1;
	while (++i < count_cmd)
	{
		if (cmd[i].command)
		{
			printf("\n******** COMMAND [%d]**************\n\n", i + 1);
			printf("\tcommand  = %s\n", cmd[i].command->cmd);
			j = -1;
			while (cmd[i].command->arg[++j])
				printf("\targument = %s\n", cmd[i].command->arg[j]);
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

t_cmd	*fill_struct_cmd(t_list *lst)
{
	t_cmd	*cmd;
	int		command_count;
	int		i;
	int		pos;
	
	command_count = command_number(lst);
	cmd = malloc(command_count * sizeof(t_cmd));
	pos = 0;
	i = 0;
	while (i < command_count)
	{
		cmd[i].command = fill_struct_command(lst, &pos);
		cmd[i].redir = fill_struct_redir(lst);
		i++;
		while (lst && lst->data->token != PIPE)
			lst = lst->next;
		if (lst && lst->data->token == PIPE)
			lst = lst->next;
		pos = 0;
	}
	print_parser(cmd, command_count);
	return (cmd);
}

