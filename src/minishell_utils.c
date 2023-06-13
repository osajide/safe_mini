/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 18:32:03 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*convert_env_to_list(char **env)
{
	int	i;
	t_env *env_lst;
	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		add_env_node_back(&env_lst,
			add_new_env_node(get_env_id(env[i]), get_env_content(env[i])));
		i++;
	}
	return (env_lst);
}