/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:03:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/14 22:26:08 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int		open_files(t_redir *redir)
{
	int	fd_in;
	int	fd_out;

	while (redir)
	{
		// ft_printf(2,"redir->file = %s\n", redir->file);
		// ft_printf(2, "redir->type = %d\n", redir->type);
		if (redir->type == REDIR_IN)
		{
			if (handle_file_in(redir))
			{
				fd_in = open(redir->file, O_RDONLY);
				if (fd_in < 0)
					return (0);
				dup2(fd_in, 0);
				close(fd_in);
			}
		//exit(general.exit_status);
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND_REDIR)
		{
			if (handle_file_out(redir))
			{
				if (redir->type == REDIR_OUT)
					fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else
					fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_out < 0)
					return (0);
				dup2(fd_out, 1);
				close(fd_out);
			}
		}
		redir = redir->next;
	}
	return (1);
}

void    execute_cmd(t_cmd *cmd, t_env **env)
{
	char	*cmd_exec;
	char	**ar;
	char	**new_env;

	if (cmd->args)
	{
		new_env = dup_lstenv(*env);
		cmd_exec = get_path_cmd(cmd, new_env);
		if (!cmd_exec)
			exit(127);
		ar = get_new_arg(cmd);
		if (execve(cmd_exec, ar, new_env) < 0)
			exit(1);
	}
}
