/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/08 16:17:39 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>
#include <string.h>

char	*expand_string(char *s, t_env *env_lst)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		// printf("========> s[%d] = %c | %d\n\n", i, s[i], s[i]);
		if (s[i] == 39)
		{
			temp =  ft_strjoin(temp, expand_inside_single_quotes(s, &i));
			// printf("\t\t\t1)-temp = %s\n", temp);
		}
		else if (s[i] == 34)
		{
			temp = ft_strjoin(temp, expand_inside_double_quotes(s, &i, env_lst));
			// printf("\t\t\t2)-temp = %s\n", temp);
		}
		else if (s[i] == '$')
		{
			temp = ft_strjoin(temp, handle_dollar_sign(s, &i, env_lst));
			// printf("\t\t\t3)-temp = %s\n", temp);
		}
		else
		{
			temp = ft_join_char(temp, s[i]);
			// printf("\t\t\t4)-temp = %s\n", temp);
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
		s[i] = expand_string(s[i], env_lst);
		i++;
	}
	return (s);
}

void	expand_cmd(t_command *command, t_env *env_lst)
{
	command->cmd = expand_string(command->cmd, env_lst);
	printf("\n---------------------------------------------------------------------\n");
	printf("\n\t\t\t\033[1;32mcommand->cmd =\033[0m (%s)\n", command->cmd);
	printf("\n---------------------------------------------------------------------\n");
	command->arg = expand_command_args(command->arg, env_lst);
	int i = 0;
	while (command->arg[i])
	{
		printf("\n---------------------------------------------------------------------\n");
		printf("\n\t\t\t\033[1;32mcommand->arg[%d] =\033[0m (%s)\n", i, command->arg[i]);
		printf("\n---------------------------------------------------------------------\n");
		i++;
	}



}