/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:01:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/05 22:43:36 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;

	minishell();
	return (0);
}
