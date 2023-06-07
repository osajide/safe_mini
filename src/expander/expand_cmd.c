/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/07 16:51:01 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>

char	*expand_command_name(char *s, t_env *env_lst)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		printf("s[%d] = %c | %d\n", i, s[i], s[i]);
		if (s[i] == 39)
		{
			expand_inside_single_quotes(s, &temp, &i);
			printf("\t\t\t1)-temp = %s\n", temp);
		}
		else if (s[i] == 34)
		{
			expand_inside_double_quotes(s, &temp, &i, env_lst);
			printf("\t\t\t2)-temp = %s\n", temp);
		}
		else if (s[i] == '$')
		{
			temp = ft_strjoin(temp, handle_dollar_sign(s, &temp, &i, env_lst));
			printf("\t\t\t3)-temp = %s\n", temp);
		}
		else
		{
			temp = ft_join_char(temp, s[i]);
			printf("\t\t\t4)-temp = %s\n", temp);
		}
		i++;
	}
	return (temp);
}

char	**expand_command_args(char **s, t_env *env_lst)
{
	char	*temp;
	int		i;
	
	i = 0;
	temp = NULL;
	while (s[i])
	{
		s[i] = expand_command_name(s[i], env_lst);
		i++;
	}
	return (s);
}

void	expand_cmd(t_command *command, t_env *env_lst)
{
	command->cmd = expand_command_name(command->cmd, env_lst);
	printf("command->cmd = %s\n", command->cmd);
	command->arg = expand_command_args(command->arg, env_lst);
	int i = 0;
	while (command->arg[i])
	{
		printf("command->arg[%d] = %s\n", i, command->arg[i]);
		i++;
	}



}