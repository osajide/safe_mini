/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 20:55:19 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>

t_cmd	*expander(t_cmd *cmd, int cmd_count, char **env)
{
	int		i;
	t_env	*env_lst;

	// printf("\n\n\033[1;31mParser finished\n***********************\033[0m\n\n");
	i = 0;
	env_lst = NULL;
	convert_to_env_list(env, &env_lst);
	while (i < cmd_count)
	{
		expand_cmd(&cmd[i], env_lst);
		i++;
	}
	return (cmd);
}
