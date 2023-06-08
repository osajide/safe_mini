/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:01:06 by osajide           #+#    #+#             */
/*   Updated: 2023/06/08 19:21:51 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum e_state
{
	IN_SQ = 1,
	IN_DQ,
	NOTHING
}	t_state;

typedef enum e_token
{
	WORD = 1,
	ENV,
	WHITE_SPACE,
	SINGLE_Q,
	DOUBLE_Q,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_REDIR,
	HEREDOC
}	t_token;

typedef struct s_data
{
	char	*content;
	t_state	state;
	t_token	token;
}	t_data;

typedef struct s_list
{
	t_data			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_args
{
	char			*argument;
	struct s_args	*next;
}	t_args;

// typedef struct s_command
// {
// 	char	*cmd;
// 	t_args	*args;
// }	t_command;

typedef struct s_redir
{
	char			*file;
	t_token			type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		*command;
	t_args		*args;
	t_redir		*redir;
}	t_cmd;

typedef struct s_env
{
	char			*id;
	char			*content;
	struct s_env	*next;
}	t_env;

#endif