/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:44:27 by osajide           #+#    #+#             */
/*   Updated: 2023/06/13 22:48:41 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	export_new_value(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (!ft_strncmp(env->id, key, ft_strlen(key)))
		{
			if (!new_value)
				return (1);
			return (env->content = new_value, 1);
		}
		env = env->next;
	}
	return (0);
}

char	*env_id(char *var)
{
	int		i;
	int		start;
	char	*env_id;

	i = 0;
	env_id = NULL;
	start = i;
	while (var[i] && var[i] != '=')
		i++;
	env_id = ft_substr(var, start, i);
	return (env_id);
}

char	*env_content(char *var)
{
	int		i;
	int		start;
	int		check_if_value;
	char	*env_content;

	i = 0;
	env_content = NULL;
	start = i;
	while (var[i] && var[i] != '=')
		i++;
	check_if_value = i;
	if (var[i] == '=')
		i++;
	if (i - check_if_value > 0)
		env_content = ft_substr(var, i, ft_strlen(var));
	return (env_content);
}

void	ft_export(t_args *args, t_env *env_lst)
{
	t_env	*temp;
	char	*ptr;

	temp = env_lst;
	if (!args)
	{
		while (temp)
		{
			printf("declare -x %s", temp->id);
			if (temp->content)
				printf("=\"%s\"\n", temp->content);
			else
				printf("\n");
			temp = temp->next;
		}	
	}
	else
	{
		while (args)
		{
			if (!export_new_value(env_lst, env_id(args->argument),  env_content(args->argument)))
			{
				ptr = ft_strchr(args->argument, '=');
				if (!ptr)
					add_env_node_back(&env_lst, add_new_env_node(args->argument, NULL));
				else
				{
					if (!ft_strncmp(ptr, "=", ft_strlen(ptr)))
						add_env_node_back(&env_lst, add_new_env_node(env_id(args->argument), ""));
					else
						add_env_node_back(&env_lst, add_new_env_node(env_id(args->argument), env_content(args->argument)));
				}
			}
			args = args->next;
		}
	}
}