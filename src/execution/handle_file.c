/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:20:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/10 20:14:02 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int handle_file(t_redir *redir)
{
	t_redir *tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (access(tmp->file, F_OK) < 0)
				return (ft_printf("%s: no such file or directory\n", type->file), 0);
			if (access(file, R_OK) < 0){
				return (ft_printf("%s: permission denied\n", type->file), 0);
		}
		if (tmp->type == REDIR_OUT)
		{
			if (access(tmp->file, W_OK) < 0)
				return (ft_printf("%s: permission denied\n", type->file), 0);
		}
		tmp = tmp->next;
	}
}