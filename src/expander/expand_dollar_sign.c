/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:33:29 by osajide           #+#    #+#             */
/*   Updated: 2023/06/07 22:07:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

char	*handle_dollar_sign(char *s, int *pos, t_env *env_lst)
{
	char	*temp;
	int		start;
	
	temp = NULL;
	(*pos)++;
	if (!s[*pos])
		return ((*pos)-- , ft_join_char(temp, '$'));
	if (!((s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= 'a' && s[*pos] <= 'z') || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos])
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else
	{
		start = *pos;
		while ((s[*pos] >= 'a' && s[*pos] <= 'z') || (s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= '0' && s[*pos] <= '9'))
			(*pos)++;
		temp = ft_substr(s, start, *pos);
		while (env_lst)
		{
			if (!ft_strncmp(temp, env_lst->id, ft_strlen(temp)))
				return ((*pos)--, env_lst->content);
			env_lst = env_lst->next;
		}
		if (!env_lst)
		{
			ft_bzero(temp, ft_strlen(temp));
			return (temp);
		}
	}
	return (temp);
}

char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst)
{
	char	*temp;
	int		start;

	temp = NULL;
	(*pos)++;
	if (s[*pos] == ' ')
	{
		start = *pos - 1;
		while (s[*pos] != 34)
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else if (!((s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= 'a' && s[*pos] <= 'z') || s[*pos] == '_'))
	{
		(*pos)++;
		start = *pos;
		while (s[*pos] != 34)
			(*pos)++;
		temp = ft_substr(s, start, *pos);
	}
	else
	{
		start = *pos;
		while ((s[*pos] >= 'a' && s[*pos] <= 'z') || (s[*pos] >= 'A' && s[*pos] <= 'Z') || (s[*pos] >= '0' && s[*pos] <= '9'))
			(*pos)++;
		temp = ft_substr(s, start, *pos);
		while (env_lst)
		{
			if (!ft_strncmp(temp, env_lst->id, ft_strlen(temp)))
				return (env_lst->content);
			env_lst = env_lst->next;
		}
		if (!env_lst)
		{
			ft_bzero(temp, ft_strlen(temp));
			return (temp);
		}
	}
	return (temp);
}
