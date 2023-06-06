/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:07:38 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/06 23:52:10 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int	i;
	int	j;
	char	*new;

	if (!s1)
		s1 = ft_calloc(1, 1);
	else if (!s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i++] = s1[j++];
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free((char *)s1);
	return (new);
}
