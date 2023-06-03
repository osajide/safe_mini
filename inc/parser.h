/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:59:07 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/03 20:07:17 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

typedef struct s_command
{
	char *cmd;
	char **arg;
	int	infile;
	int	outfile;
}	t_command;

typedef struct s_redir
{
	char	*arg;
	t_token	type;
}	t_redir;

typedef struct s_cmd
{
	t_command	*command;
	t_redir		redir_left;
	t_redir		redir_right;
	struct s_cmd		*next;
}	t_cmd;

t_list  *return_final_list(t_list *lst);

#endif