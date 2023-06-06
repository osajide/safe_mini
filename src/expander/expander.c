/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:11:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/06 20:24:00 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>

char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst)
{
	char	*var;
	char	*temp;
	int		start;

	var = NULL;
	temp = NULL;
	(*pos)++;
	if (s[*pos] == ' ')
	{
		start = *pos - 1;
		while (s[*pos] != 34)
			(*pos)++;
		var = ft_substr(s, start, *pos);
	}
	else if (!((s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= 'a' && s[*pos] <= 'z') || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos] != 34)
			(*pos)++;
		var = ft_substr(s, start, *pos);
	}
	else
	{
		start = *pos;
		while ((s[*pos] >= 'a' && s[*pos] <= 'z') || (s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= '0' && s[*pos] <= '9'))
			(*pos)++;
		temp = ft_substr(s, start, *pos);
		while (env_lst)
		{
			if (!ft_strncmp(temp, env_lst->id, ft_strlen(temp)))
				return (env_lst->content);
			env_lst = env_lst->next;
		}
	}
	return (var);
}

void	expand_inside_single_quotes(char *s, char **temp, int *pos)
{
	int	start;

	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 39)
		(*pos)++;
	*temp = ft_strjoin(*temp, ft_substr(s, start, *pos));
	// (*pos)++;
}

void	expand_inside_double_quotes(char *s, char **temp, int *pos, t_env *env_lst)
{
	int	start;

	(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != 34)
	{
		if (s[*pos] == '$' && s[*pos + 1] != 34)
		{
			*temp = ft_substr(s, start, *pos);
			*temp = ft_strjoin(*temp, handle_dollar_sign_inside_d_quotes(s, pos, env_lst));
			return ;
		}
		(*pos)++;
	}
	*temp = ft_strjoin(*temp, ft_substr(s, start, *pos));
}

void	expand_command_name(char *s, t_env *env_lst)
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
		else if (s[i] == 34)
		{
			expand_inside_double_quotes(s, &temp, &i, env_lst);
			printf("\t\t\t\t\t2)-temp = %s\n", temp);
		}
		i++;
	}
}

void	expand_cmd(t_command *command, t_env *env_lst)
{
	expand_command_name(command->cmd, env_lst);








	
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
		expand_cmd(cmd[i].command, env_lst);
		// printf("---------------> cmd[%d].command->cmd = %s\n", i, cmd[i].command->cmd);
		i++;
	}
	return (cmd);
}
