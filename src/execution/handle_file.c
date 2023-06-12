/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:20:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 23:47:30 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	handle_file_out(char *file)
{
	if (access(file, W_OK) < 0)
		return (general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", file), 0);
	return (1);
}

int handle_file_in(char *file)
{
	if (access(file, F_OK) < 0)
		return (general.exit_status = 1, ft_printf(2, "minishell: No such file or directory\n"), 0);
	if (access(file, R_OK) < 0)
		return (general.exit_status = 1, ft_printf(2, "minishell: %s: Permission denied\n", file), 0);
	return (1);
}