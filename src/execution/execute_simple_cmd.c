/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:07:44 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 21:55:27 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int execute_simple_cmd(t_cmd *cmd, char **env)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return (printf("an error in create process\n"), 0);
// 	if (pid == 0)
// 	{
// 		if (!open_files(cmd->redir))
// 			return (0);
// 		execute_cmd(cmd, general, env);
// 	}
// 	waitpid(pid, 0, 0);
// 	return (1);
// }