/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/09 18:07:19 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	clear_args_list(t_args *args)
{
	t_args	*tmp;
	
	while (args)
	{
		tmp = args;
		args = args->next;
		free(tmp->argument);
		free(tmp);
	}
}

void	expand_args_string(char *s, t_env *env_lst, t_args **new_args)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;

	printf("dkhel l expand arg string function\n");
	i = 0;
	temp = NULL;
	var = NULL;
	while (s[i])
	{
		if (s[i] == 39)
			temp =  ft_strjoin(temp, expand_inside_single_quotes(s, &i));
		else if (s[i] == 34)
			temp = ft_strjoin(temp, expand_inside_double_quotes(s, &i, env_lst));
		else if (s[i] == '$')
		{
			var = handle_dollar_sign(s, &i, env_lst);
			if (if_should_split(var))
			{
				replace_var(temp, var, new_args);
				return ;
			}
			else
				temp = ft_strjoin(temp, var);
		}
		else
			temp = ft_join_char(temp, s[i]);
		i++;
	}
	printf("-----------> temp = (%s)\n", temp);
	add_args_node_back(new_args, new_args_node(temp));
}

t_args	*expand_args(t_args *args, t_env *env_lst)
{
	t_args	*new_args;
	
	new_args = NULL;
	while (args)
	{
		expand_args_string(args->argument, env_lst, &new_args);
		args = args->next;
	}
	clear_args_list(args);
	return (new_args);
}

void	expand_cmd(t_cmd *cmd, t_env *env_lst)
{	
	cmd->args = expand_args(cmd->args, env_lst);
	t_args	*tmp;
	tmp = cmd->args;
	while (tmp)
	{
		printf("\n---------------------------------------------------------------------\n");
		printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->args->argument =\033[0m (%s)\n", tmp->argument);
		printf("\n---------------------------------------------------------------------\n");
		tmp = tmp->next;
	}
	// printf("\n---------------------------------------------------------------------\n");
	// printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->args->argument =\033[0m (%s)\n", cmd->args->argument);
	// printf("\n---------------------------------------------------------------------\n");
}









/*
echo " $ "
echo " $? "
echo $''$""$' '$" "$'?'$"?"$'? '$"? "" $ "" $? "
echo $'USER'
echo $"USER"
echo $'USER '
echo $"USER "
echo " $ "
echo " $USER "
echo $'USERR'
echo $"USERR"
echo $'USERR '
echo $"USERR "
echo " $ "
echo " $USERR "
echo $''$""$' '$" "$'USER'$"USER"$'USER '$"USER "" $ "" $USER "
echo $?$?$?$?$?$?$?$
echo $'USER'
echo $"USER"
echo '$USER'
echo "$USER"
echo "'$USER'"
echo '"$USER"'
echo $USER"'"
echo $USER""
echo ''$USER
echo $'USER'$"USER"'$USER'"$USER""'$USER'"'"$USER"'$USER"'"$USER""''$USER
echo $?$USER
export 'USER'=YO
echo $'USER'
exit

Stranges cases : not supported
echo $''
echo $""
echo $' '
echo $" "
echo $'?'
echo $"?"
echo $'? '
echo $"? "
echo " $"USER
*/