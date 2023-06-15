/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:28 by osajide           #+#    #+#             */
/*   Updated: 2023/06/15 14:58:35 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    read_herdoc(t_redir *redir)
{
    char	*line;
	char	*hrdc;
	int		save_fd[2];

	hrdc = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			pipe(general.fd);
			save_fd[0] = dup(STDIN_FILENO);
			save_fd[1] = dup(STDOUT_FILENO);
			while (1)
			{
				ft_printf(1, "> ");
					line = get_next_line(0);
					if (!ft_strncmp(redir->file, ft_strtrim(line, "\n"), ft_strlen(redir->file)))
						break;
					hrdc = ft_strjoin(hrdc, line);
			}
			// dup2(general.fd[1], 1);
			// dup2(general.fd[0], 0);
			// close(general.fd[1]);
			// close(general.fd[0]);
			ft_printf(1, "%s", hrdc);
			// close(general.fd[1]);
			// close(general.fd[0]);
			dup2(save_fd[0], 0);
			dup2(save_fd[1], 1);
		}
		redir = redir->next;
	}
}