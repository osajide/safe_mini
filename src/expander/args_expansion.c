/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:50 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 18:33:28 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_args_string(char *s, t_env *env_lst, t_args **new_args)
{
	int		i;
	char	*temp;
	char	*var;
	char	**split;

	i = 0;
	temp = NULL;
	var = NULL;
	if (!s)
		return ;
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
