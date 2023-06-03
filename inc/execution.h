/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:56:33 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/03 19:52:50 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_exec
{
	char	**cmd;
	int		count_cmd;
	int		infile;
	int		outfile;
	struct s_exec *next;
}	t_exec;

#endif
