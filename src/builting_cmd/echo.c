/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:13:36 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/13 21:36:26 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *join_with_free(char *str, char *buff)
{
	char *tmp;
	tmp = ft_strjoin(str, buff);
	if (!tmp)
		return (NULL);
	free(str);
	return tmp;
}

void	ft_echo(t_args *args)
{
	char	*temp;

	if (!args)
	{
		printf("\n");
		return ;
	}
	if (args)
	{
		temp = args->argument;
		if (!ft_strncmp(temp, "-n", ft_strlen(temp)))
			args = args->next;
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
	if (ft_strncmp(temp, "-n", ft_strlen(temp)))
		printf("\n");
}
