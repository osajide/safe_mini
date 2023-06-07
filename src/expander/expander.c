/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/07 21:56:55 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>

char	*expand_inside_single_quotes(char *s, int *pos)
{
	char	*temp;
	int		start;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 39)
		(*pos)++;
	temp = ft_substr(s, start, *pos);
	return (temp);
}

char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst)
{
	int		start;
	char	*temp;

	temp = NULL;
	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$' && s[*pos + 1] != 34)
		{
			temp = ft_strjoin(temp, handle_dollar_sign_inside_d_quotes(s, pos, env_lst));
			(*pos)--;
		}
		else
		{
			temp = ft_join_char(temp, s[*pos]);
		}
		(*pos)++;
	}
	return (temp);
}

t_cmd	*expander(t_cmd *cmd, int cmd_count, char **env)
{
	int		i;
	t_env	*env_lst;

	printf("\n\n\033[1;31mParser finished\n***********************\033[0m\n\n");
	i = 0;
	env_lst = NULL;
	convert_to_env_list(env, &env_lst);
	while (i < cmd_count)
	{
		expand_cmd(cmd[i].command, env_lst);
		// expand_redir(cmd[i].redir, env_lst);
		// printf("---------------> cmd[%d].command->cmd = %s\n", i, cmd[i].command->cmd);
		i++;
	}
	return (cmd);
}
