/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:02:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/17 16:45:58 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>

char	*get_path(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (env[i] && ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

char	**split_path(char *path)
{
	char	**new_path;

	new_path = ft_split(path, ':');
	return (new_path);
}

char	*check_path(char *cmd, char *path)
{
	char	**new_path;
	char	*last_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
	}
	new_path = split_path(path);
	i = -1;
	while (new_path[++i] && *cmd)
	{
		last_path = ft_strjoin(new_path[i], "/");
		last_path = ft_strjoin(last_path, cmd);
		if (access(last_path, F_OK) == 0)
			return (last_path);
		free(last_path);
	}
	if (ft_strchr(cmd, '/'))
		return (ft_printf(2, "minishell: %s: No such file or directory\n", cmd), NULL);
	ft_printf(2, "minishell: %s: command not found\n", cmd);
	return (NULL);
}

char	*get_path_cmd(t_cmd *cmd, char **env)
{
	int i;
	char *path_cmd;
	char	*path;
	
	path_cmd = get_path(env);
	if (!path_cmd)
	{
		if (access(cmd->args->argument, F_OK))
			return (ft_printf(2, "minishell: %s: No such file or directory\n", cmd->args->argument), NULL);
		else if (access(cmd->args->argument, X_OK))
			return (ft_printf(2, "minishell: %s: Permission denied\n", cmd->args->argument), NULL);
		else
			return (cmd->args->argument);
	}
	path = check_path(cmd->args->argument, path_cmd);
	return (path);
}
