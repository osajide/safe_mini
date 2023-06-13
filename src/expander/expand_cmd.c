/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:26:45 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 22:19:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	expand_redir_string(t_redir *redir, t_env *env_lst, t_redir **new_redir)
{
	int		i;
	char	*temp;
	char	*var;
	char	*ambiguous;
	int		is_dollar;

	i = 0;
	ambiguous = redir->file;
	temp = NULL;
	var = NULL;
	if (redir->type != HEREDOC)
	{
		while (redir->file[i])
		{
			is_dollar = 0;
			if (redir->file[i] == 39)
				temp =  ft_strjoin(temp, expand_inside_single_quotes(redir->file, &i));
			else if (redir->file[i] == 34)
				temp = ft_strjoin(temp, expand_inside_double_quotes(redir->file, &i, env_lst));
			else if (redir->file[i] == '$')
			{
				var = handle_dollar_sign(redir->file, &i, env_lst);
				var = replace_spaces(var);
				temp = ft_strjoin(temp, var);
				is_dollar = 1;
			}
			else
				temp = ft_join_char(temp, redir->file[i]);
			i++;
		}
		
		if (split_word_count(temp, "\x06") != 1)
		{
			if (!is_dollar && temp && !*temp)
			{
				redir->is_ambiguous = 0;
				// general.exit_status = 1;
				ambiguous = ft_strtrim(ambiguous, "\"'");
				ft_printf(2, "minishell: %s: No such file or directory\n", ambiguous);
				return (0);
			}
			redir->is_ambiguous = 1;
			// general.exit_status = 1;
			ft_printf(2, "minishell: %s: ambiguous redirect\n", ambiguous);
			return (0);
		}
		else
			add_redir_node_back(new_redir, new_redir_node(temp, redir->type));
	}
	return (1);
}

t_redir	*expand_redir(t_redir *redir, t_env *env_lst)
{
	t_redir	*new_redir;
	
	new_redir = NULL;
	while (redir)
	{
		if(!expand_redir_string(redir, env_lst, &new_redir))
			general.should_exec = 0;
		redir = redir->next;
	}
	clear_redir_list(redir);
	return (new_redir);
}
