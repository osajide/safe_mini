/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/09 22:49:18 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	expand_args_string(char *s, t_env *env_lst, t_args **new_args)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;

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
				replace_var_in_args_list(temp, var, new_args);
				return ;
			}
			else
				temp = ft_strjoin(temp, var);
		}
		else
			temp = ft_join_char(temp, s[i]);
		i++;
	}
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

void	expand_redir_string(t_redir *redir, t_env *env_lst, t_redir **new_redir)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;

	i = 0;
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
				var = handle_dollar_sign(temp, &i, env_lst);
				temp = ft_strjoin(temp, var);
				if (split_word_count(temp, "\t ") > 1)
				{
					ft_putstr_fd("minishell: ambiguous redirect\n", 2);
					return ;
				}
				else
				{
					if (if_should_split(temp))
					{
						split = ft_split_charset(temp, "\t ");
						while (*split)
						{
							temp = ft_strjoin(temp, ft_strdup(*split));
							split++;
						}
					}
				} 
			}
			else
				temp = ft_join_char(temp, redir->file[i]);
			i++;
		}
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
	// printf("\n---------------------------------------------------------------------\n");
	// printf("\n\t\033\033[1;31m[expand_cmd]\033[0m  \033[1;32mcmd->args->argument =\033[0m (%s)\n", cmd->args->argument);
	// printf("\n---------------------------------------------------------------------\n");
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