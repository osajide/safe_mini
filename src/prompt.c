/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:07:56 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/17 16:56:59 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../gnl/get_next_line.h"
#include <stdlib.h>

char	*display_prompt(void)
{
	char	*line;

	if (isatty(0))
		line = readline("> minishell $ ");
	else
	{
		line = get_next_line(0);
		line = ft_strtrim(line, "\n");
	}
	if (!line)
		exit(general.exit_status);
	if (line && *line)
		add_history(line);
	// free(str);
	return (line);
}
