/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:13:36 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/14 14:32:43 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

int	compare_char(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_args *args)
{
	char	*temp;
	int		compare;

	compare = 0;
	if (!args)
	{
		printf("\n");
		return ;
	}
	if (args)
	{
		while (args && args->argument[0] == '-' && compare_char(args->argument + 1, 'n', ft_strlen(args->argument + 1)))
		{
			temp = args->argument;
			args = args->next;
		}
		if (args)
		{
			while (args)
			{
				printf("%s", args->argument);
				if (args->next)
					printf(" ");
				args = args->next;
			}
		}
	}
	if (!compare_char(temp + 1, 'n', ft_strlen(temp + 1)))
		printf("\n");
}
