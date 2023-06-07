/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:33:29 by osajide           #+#    #+#             */
/*   Updated: 2023/06/07 16:23:07 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

char	*handle_dollar_sign(char *s, char **temp, int *pos, t_env *env_lst)
{
	char	*var;
	int		start;
	
	var = NULL;
	(*pos)++;
	if (!s[*pos])
		*temp = ft_strjoin(*temp, "$");
	else if (!((s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= 'a' && s[*pos] <= 'z') || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos])
			(*pos)++;
		var = ft_substr(s, start, *pos);
	}
	else
	{
		start = *pos;
		while ((s[*pos] >= 'a' && s[*pos] <= 'z') || (s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= '0' && s[*pos] <= '9'))
			(*pos)++;
		*temp = ft_substr(s, start, *pos);
		(*pos)--;
		while (env_lst)
		{
			if (!ft_strncmp(*temp, env_lst->id, ft_strlen(*temp)))
				return (env_lst->content);
			env_lst = env_lst->next;
		}
		if (!env_lst)
		{
			ft_bzero(*temp, ft_strlen(*temp));
			return (*temp);
		}
	}
	return (var);
}
