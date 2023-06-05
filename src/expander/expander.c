/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/05 19:31:45 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

int	should_expand(t_command *command)
{
	int	i;

	i = 0;
	while (command->cmd[i])
	{
		
	}
	
	return (0);
}

t_cmd	*expander(t_cmd *cmd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		should_expand(cmd[i].command);
	}
	return (cmd);
}