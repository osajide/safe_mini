/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/06 16:09:08 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>

void	handle_dollar_sign(char *s)
{
	
}

void	expand_inside_single_quotes(char *s, char **temp, int *pos)
{
	int	start;

	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 39)
		(*pos)++;
	*temp = ft_strjoin(*temp, ft_substr(s, start, *pos));
	(*pos)++;
}

void	expand_inside_double_quotes(char *s, char **temp, int *pos)
{
	int	start;

	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$')
			handle_dollar_sign(s);
		(*pos)++;
	}
	*temp = ft_strjoin(*temp, ft_substr(s, start, *pos));
	(*pos)++;
}

void	expand_command_name(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == 39)
		{
			expand_inside_single_quotes(s, &temp, &i);
			printf("\t\t\t\t\t1)-temp = %s\n", temp);
			printf("======> s[%d] = %c | %d\n", i, s[i], s[i]);
		}
		if (s[i] == 34)
		{
			expand_inside_double_quotes(s, &temp, &i);
			printf("\t\t\t\t\t2)-temp = %s\n", temp);
		}
		i++;
	}
}

void	expand_cmd(t_command *command)
{
	expand_command_name(command->cmd);
}

t_cmd	*expander(t_cmd *cmd, int cmd_count, char **env)
{
	int		i;
	t_env	*env_lst;

	i = 0;
	env_lst = NULL;
	convert_to_env_list(env, &env_lst);
	while (i < cmd_count)
	{
		expand_cmd(cmd[i].command);
		// printf("---------------> cmd[%d].command->cmd = %s\n", i, cmd[i].command->cmd);
		i++;
	}
	return (cmd);
}
