/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:56:33 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/12 23:25:28 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"
#include "types.h"

#define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

int		execute_simple_cmd(t_cmd *cmd, t_general *general, char **env);
int		execute_multiple_cmd(t_cmd *cmd, t_general *general, char **env);
void	execute_cmd(t_cmd *cmd, t_general *general, char **env);
int		open_files(t_redir *redir, t_general *general);

/********* UTILS FUNCTION ************/

char	**get_new_arg(t_cmd *cmd);
char	*get_path_cmd(t_cmd *cmd, char **env);

/*********** handle in out file ***************/

int handle_file_in(char *file);
int	handle_file_out(char *file);

#endif
