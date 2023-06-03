/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:18:34 by osajide           #+#    #+#             */
/*   Updated: 2023/06/03 20:27:21 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include "types.h"
# include "lexer.h"

/************ prompt ***************/

char	*display_prompt(void);

/* ========== handling_input ========= */

void	check_input(char *line);
int		check_quotes(char *str);
int		check_pipes(char *str, char c);

/************ main function ********/

void	minishell(void);
;
/************ CHECK TYPE COMMAND *************/

// void check_type_cmd(t_list *lst);

#endif
