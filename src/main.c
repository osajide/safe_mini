/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:01:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/06 19:47:38 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	// int i = 0;
	// while (env[i])
	// {
	// 	puts(env[i]);
	// 	i++;
	// }
	minishell(env);
	return (0);
}
