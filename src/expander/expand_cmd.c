/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 18:19:20 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
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

int	expand_redir_string(t_redir *redir, t_env *env_lst, t_redir **new_redir, t_general *general)
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
				var = replace_spaces(var);
				temp = ft_strjoin(temp, var);
			}
			else
				temp = ft_join_char(temp, redir->file[i]);
			i++;
		}
		if (split_word_count(temp, "\x06") != 1)
		{
			general->exit_status = 1;
			ft_printf(2, "minishell: %s: ambiguous redirect\n", ambiguous);
			return 0;
		}
		else
			add_redir_node_back(new_redir, new_redir_node(temp, redir->type));
	}
	return 1;
}

t_redir	*expand_redir(t_redir *redir, t_env *env_lst, t_general *general)
{
	t_redir	*new_redir;
	
	new_redir = NULL;
	while (redir)
	{
		if(!expand_redir_string(redir, env_lst, &new_redir, general))
			return NULL;
		redir = redir->next;
	}
	clear_redir_list(redir);
	return (new_redir);
}
