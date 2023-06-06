/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:51:02 by osajide           #+#    #+#             */
/*   Updated: 2023/06/06 22:04:28 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include "types.h"
# include "lexer.h"

t_cmd	*expander(t_cmd *cmd, int cmd_count, char **env);

/************** env linked list *************/

t_env	*add_new_env_node(char *id, char *content);
void	add_env_node_back(t_env **env, t_env *new_env_node);
char	*get_env_id(char *env_var);
void	convert_to_env_list(char **env, t_env **env_lst);
char	*handle_dollar_sign(char *s, char **temp, int *pos, t_env *env_lst);
#endif