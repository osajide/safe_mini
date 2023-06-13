/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:07:56 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 22:19:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../gnl/get_next_line.h"
#include <stdlib.h>

char	*display_prompt(void)
{
	char	*line;
	// char	**dir;
	// char	*str;
	// char	*prm;
	// char	*user;
	// char	path[PATH_MAX];
	// int		i;
	
	// getcwd(path, sizeof(path));
	// user = getenv("USER");
	// dir = ft_split((char *)path, '/');
	// i = -1;
	// while (dir[++i])
	// 	;
	// str = ft_strjoin("\033[1;33m[", dir[i - 1]);
	// str = ft_strjoin(str, "]$ \033[0m");
	// user = ft_strjoin("\033[1;34m -> minishell@", user);
	// prm = ft_strjoin(user, " : \033[0m");
	// str = join_with_free(prm, str);
	if (isatty(0))
		line = readline("\033[1;33m> minishell $ \033[0m");
	else
	{
		line = get_next_line(0);
		line = ft_strtrim(line, "\n");
	}
	if (!line)
		exit(general.exit_status);
	if(line)
		add_history(line);
	// free(str);
	return (line);
}
