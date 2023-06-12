/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:00:51 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 21:59:30 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include <stdio.h>

int execute_multiple_cmd(t_cmd *cmd, t_general *general, char **env)
{
	int	i;
	int	fd[2];
	int prv_fd;
	int	*pid;
	int	file;
	char	*cmd_exec;
	char **ar;

	i = -1;
	prv_fd = 0;
	pid = malloc(sizeof(int) * general->nbr_cmd);
	while (++i < general->nbr_cmd)
	{
		// printf("cmd[%d].args->argument = (%s)\n", i, cmd[i].args->argument);
		if (i < general->nbr_cmd - 1)
		{
			if (pipe(fd) < 0)
				return (printf("an error in create pipe\n"), 0);
		}
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("an error in create process\n"), 0);
		if (pid[i] == 0)
		{
			if (i < general->nbr_cmd - 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if (i > 0)
			{
				dup2(prv_fd, 0);
				close(fd[0]);
			}
			if (!open_files(cmd[i].redir, general))
				exit(1);
			execute_cmd(&cmd[i], general, env);
		}
		else
		{
			if (i > 0)
				close(prv_fd);
			prv_fd = fd[0];
			if (i < general->nbr_cmd - 1)
				close(fd[1]);
		}
	}
	i = -1;
	while (++i < general->nbr_cmd)
		waitpid(pid[i], 0, 0);
	return (1);
}

