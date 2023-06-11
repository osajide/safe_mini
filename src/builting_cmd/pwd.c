/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:59:04 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/11 16:38:37 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd()
{
	char pwd[PATH_MAX];
	char *path;

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);;
}