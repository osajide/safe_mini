/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:51:02 by osajide           #+#    #+#             */
/*   Updated: 2023/06/08 19:33:28 by osajide          ###   ########.fr       */
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

/*************** expander **************/

char	*handle_dollar_sign(char *s, int *pos, t_env *env_lst);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);
char	*expand_inside_single_quotes(char *s, int *pos);
char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst);
char	*expand_string(char *s, t_env *env_lst);
t_args	*expand_command_args(t_args *args, t_env *env_lst);
void	expand_cmd(t_cmd *cmd, t_env *env_lst);
char	*handle_dollar_sign_inside_d_quotes(char *s, int *pos, t_env *env_lst);

/*************** expand quotes **************/

char	*expand_inside_single_quotes(char *s, int *pos);
char	*expand_inside_double_quotes(char *s, int *pos, t_env *env_lst);

#endif