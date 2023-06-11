/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:04:31 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/11 20:52:38 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

char	**get_new_arg(t_cmd *cmd)
{
	char **new;
	t_args *tmp;
	int	i;
	int len;
	
	i = -1;
	len = 0;
	tmp = cmd->args;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (0);
	i = 0;
	tmp = cmd->args;
	while (tmp)
	{
		new[i++] = ft_strdup(tmp->argument);
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}