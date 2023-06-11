/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/11 15:16:05 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*replace_spaces(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] =='\t' || var[i] == ' ')
			var[i] = 6;
		i++;
	}
	return (var);
}

void	expand_redir_string(t_redir *redir, t_env *env_lst, t_redir **new_redir)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;
	char	*ambiguous;

	i = 0;
	ambiguous = redir->file;
	temp = NULL;
	var = NULL;
	if (redir->type != HEREDOC)
	{
		while (redir->file[i])
		{
			if (redir->file[i] == 39)
				temp =  ft_strjoin(temp, expand_inside_single_quotes(redir->file, &i));
			else if (redir->file[i] == 34)
				temp = ft_strjoin(temp, expand_inside_double_quotes(redir->file, &i, env_lst));
			else if (redir->file[i] == '$')
			{
				var = handle_dollar_sign(redir->file, &i, env_lst);
				// printf("temp before joining with var : (%s)\n", temp);
				// printf("var before : %s\n", var);
				var = replace_spaces(var);
				// printf("var after : %s\n", var);
				temp = ft_strjoin(temp, var);
				// printf("temp after joining with var : (%s)\n", temp);
				// if (split_word_count(temp, "\x06") != 1)
				// {
				// 	// ft_putstr_fd("minishell: %s: ambiguous redirect\n", 2);
				// 	printf("------------------\n\n");
				// 	printf("minishell: %s: ambiguous redirect\n", ambiguous);
				// 	printf("------------------\n");
				// 	// return ;
				// }
			}
			else
				temp = ft_join_char(temp, redir->file[i]);
			i++;
		}
		if (split_word_count(temp, "\x06") != 1)
			printf("minishell: %s: ambiguous redirect\n", ambiguous);
		else
			add_redir_node_back(new_redir, new_redir_node(temp, redir->type));
	}
}

t_redir	*expand_redir(t_redir *redir, t_env *env_lst)
{
	t_redir	*new_redir;
	
	new_redir = NULL;
	while (redir)
	{
		expand_redir_string(redir, env_lst, &new_redir);
		redir = redir->next;
	}
	clear_redir_list(redir);
	return (new_redir);
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
	cmd->redir = expand_redir(cmd->redir, env_lst);
	// printf("cmd->redir->file = (%s)\n", cmd->redir->file);
	t_redir	*tmp2;
	tmp2 = cmd->redir;
	while (tmp2)
	{
		printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->redir->file =\033[0m (%s)\n", tmp2->file);
		printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->redir->type =\033[0m %d\n", tmp2->type);
		printf("\n				>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		tmp2 = tmp2->next;
	}
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