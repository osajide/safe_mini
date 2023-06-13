/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:50:25 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 20:30:03 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "types.h"

/************* BUILIN COMMAND ************/

void	ft_echo(t_args *args);
void    ft_pwd(t_env *env);
void	change_dir(t_args *arg, t_env *env);
void	ft_export(t_args *args, t_env *env_lst);


/************** BUILTIN UTILS ************/

char *join_with_free(char *str, char *buff);

#endif