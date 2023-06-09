/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/17 18:26:32 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_cmd(t_cmd *cmd, t_env *env_lst)
{	
	cmd->args = expand_args(cmd->args, env_lst);
	// t_args	*tmp;
	// tmp = cmd->args;
	// while (tmp)
	// {
	// 	printf("\n---------------------------------------------------------------------\n");
	// 	printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->args->argument =\033[0m (%s)\n", tmp->argument);
	// 	printf("\n---------------------------------------------------------------------\n");
	// 	tmp = tmp->next;
	// }
	cmd->redir = expand_redir(cmd->redir, env_lst);
	// if(!cmd->redir)
	// 	return (0);
	// printf("cmd->redir->file = (%s)\n", cmd->redir->file);
	// t_redir	*tmp2;
	// tmp2 = cmd->redir;
	// while (tmp2)
	// {
	// 	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	// 	printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->redir->file =\033[0m (%s)\n", tmp2->file);
	// 	printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->redir->type =\033[0m %d\n", tmp2->type);
	// 	printf("\n				>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	// 	tmp2 = tmp2->next;
	// }
}

t_cmd	*expander(t_cmd *cmd, t_env *env_lst)
{
	int	i;

	i = 0;
	while (i < general.nbr_cmd)
	{
		expand_cmd(&cmd[i], env_lst);
		i++;
	}
	return (cmd);
}
