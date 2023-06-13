/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:12:54 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 18:41:36 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	change_dir(t_args *arg, t_env *env)
{

	char s[PATH_MAX];
	char	*path;
	char	*home;

	if (!arg)
	{
		home = ft_getenv(env, "HOME");	
		if (chdir(home) < 0)
			perror(home);
		change_value_env(env, "PWD", home);
	}
	else
	{
		if (chdir(arg->argument) < 0)
		{
			ft_printf(2, "minishell: cd: %s: No such file or directory\n", arg->argument);
		}
		path = getcwd(s, PATH_MAX);
		change_value_env(env, "PWD", path);
	}
}