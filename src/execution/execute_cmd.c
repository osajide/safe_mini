/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:03:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 23:54:56 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int		open_files(t_redir *redir, t_general *general)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (handle_file_in(redir->file))
			{
				general->fd_in = open(redir->file, O_RDONLY);
				if (general->fd_in < 0)
					return (0);
				dup2(general->fd_in, 0);
				close(general->fd_in);
			}
			exit(0);
		}
		else if (redir->type == REDIR_OUT)
		{
			// if (handle_file_out(redir->file))
			// {
				general->fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (general->fd_out < 0)
					return (perror(redir->file), 0);
				dup2(general->fd_out, 1);
				close(general->fd_out); 
			// }
		}
		redir = redir->next;
	}
	return (1);
}

void    execute_cmd(t_cmd *cmd, t_general *general, char **env)
{
	char	*cmd_exec;
	char	**ar;

	if (cmd->args)
	{
		cmd_exec = get_path_cmd(cmd, env);
		if (!cmd_exec)
			exit(127);
		ar = get_new_arg(cmd);
		if (execve(cmd_exec, ar, env) < 0)
			perror(cmd->args->argument);
	}
	exit (0);
}