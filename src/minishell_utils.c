/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:51 by osajide           #+#    #+#             */
/*   Updated: 2023/06/17 17:26:51 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*join_with_free(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (tmp);
}

void	clear_lst(t_list *lst)
{
	t_list	*cur;
	
	if (!lst)
		return ;
	while (lst)
	{
		cur  = lst;
		lst = lst->next;
		free(cur);
		cur = NULL;
	}
}

void	free_2d_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

t_env	*convert_env_to_list(char **env)
{
	int	i;
	t_env *env_lst;
	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		add_env_node_back(&env_lst,
			add_new_env_node(get_env_id(env[i]), get_env_content(env[i])));
		i++;
	}
	return (env_lst);
}