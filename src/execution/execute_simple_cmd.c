/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:07:44 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/10 15:41:51 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_simple_cmd(t_cmd *cmd, t_general *general, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (printf("an error in create process\n"), 0);
	if (pid == 0)
	{
		if (!open_files(cmd->redir, general))
			return (0);
		execute_cmd(cmd, general, env);
	}
	waitpid(pid, 0, 0);
	return (1);
}