/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:20:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/14 13:08:40 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_file_out(t_redir *redir)
{
	if (redir->is_ambiguous == 1)
		return (general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	if (!access(redir->file, F_OK))
	{
		if (access(redir->file, W_OK) < 0)
			return (general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	}
	return (1);
}

int handle_file_in(t_redir *redir)
{
	if (redir->is_ambiguous == 1)
		return (general.exit_status = 1, ft_printf(2, "minishell: %s: ambiguous redirect\n", redir->file), 0);
	if (access(redir->file, F_OK) < 0)
		return (general.exit_status = 1, ft_printf(2, "minishell: No such file or directory\n"), 0);
	if (access(redir->file, R_OK) < 0)
		return (general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", redir->file), 0);
	return (1);
}
