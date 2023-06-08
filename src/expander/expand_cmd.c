/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/08 19:39:57 by osajide          ###   ########.fr       */
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

t_args	*expand_command_args(t_args *args, t_env *env_lst)
{
	t_args	*temp;
	int		i;
	
	i = 0;
	temp = args;
	while (temp)
	{
		temp->argument = expand_string(temp->argument, env_lst);
		temp = temp->next;
	}
	return (args);
}

void	expand_cmd(t_cmd *cmd, t_env *env_lst)
{
	t_args	*temp;
	
	cmd->command = expand_string(cmd->command, env_lst);
	printf("\n---------------------------------------------------------------------\n");
	printf("\n\t\t\t\033[1;32mcmd->command =\033[0m (%s)\n", cmd->command);
	printf("\n---------------------------------------------------------------------\n");
	cmd->args = expand_command_args(cmd->args, env_lst);
	temp = cmd->args;
	while (temp)
	{
		printf("\n---------------------------------------------------------------------\n");
		printf("\n\t\t\t\033[1;32mcommand->args->argument =\033[0m (%s)\n", temp->argument);
		printf("\n---------------------------------------------------------------------\n");
		temp = temp->next;
	}



}