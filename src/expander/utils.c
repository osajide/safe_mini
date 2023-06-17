/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:03:15 by osajide           #+#    #+#             */
/*   Updated: 2023/06/17 18:23:35 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*trim_with_free(char const *s1, char const *set)
{
	char	*strim;
	
	strim = ft_strtrim(s1, set);
	if (s1)
		free((char *)s1);
	return (strim);
}