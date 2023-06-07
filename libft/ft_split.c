/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:30:15 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/07 23:09:03 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_check(char const *str, char c)
// {
// 	int	i;
// 	int	word;

// 	word = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i + 1] == c || str[i + 1] == 0) && str[i] != c)
// 			word++;
// 		i++;
// 	}
// 	return (word);
// }

// static int	ft_strcpy(char *dest, char const *src, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] && src[i] != c)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (i);
// }

// static int	ft_strlen_e(const char *s, char c)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i] && s[i] != c)
// 		;
// 	return (i);
// }

// static char	**slice(const char *s, char c, char **new)
// {
// 	int	i;
// 	int	index;

// 	i = 0;
// 	index = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c && s[i])
// 			i++;
// 		if (s[i])
// 		{
// 			new[index] = (char *) malloc(ft_strlen_e(&s[i], c) + 1);
// 			if (!new[index])
// 				return (0);
// 			i += ft_strcpy(new[index], &s[i], c);
// 			index++;
// 		}
// 	}
// 	new[index] = 0;
// 	return (new);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		wc;
// 	char	**dst;

// 	if (!s)
// 		return (0);
// 	wc = ft_check(s, c);
// 	dst = (char **)malloc(sizeof(char *) * (wc + 1));
// 	if (!dst)
// 		return (0);
// 	slice(s, c, dst);
// 	return (dst);
// }

static	int	in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	w_count(char const *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (in_charset(s[i], charset))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !in_charset(s[i], charset))
			i++;
	}
	return (count);
}

static	int	w_len(char const *s, char *charset)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (in_charset(s[i], charset))
		i++;
	while (s[i] && !in_charset(s[i], charset))
	{
		len++;
		i++;
	}
	return (len);
}

static	char	*w_fil(char const *s, char *charset)
{
	int		i;
	int		j;
	char	*w;

	i = 0;
	j = 0;
	w = ft_calloc(w_len(s, charset) + 1, sizeof(char));
	while (in_charset(s[i], charset))
		i++;
	if (s[i] && !in_charset(s[i], charset))
		ft_memcpy(w, s, w_len(s, charset));
	return (w);
}

char	**ft_split(char const *s, char *charset)
{
	int		i;
	int		j;
	char	**split;

	if (!s)
		return (0);
	i = 0;
	j = w_count(s, charset);
	split = malloc((j + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (*s && j)
	{
		while (in_charset(*s, charset))
			s++;
		split[i] = w_fil(s, charset);
		s = s + w_len(s, charset);
		while (*s && in_charset(*s, charset))
			s++;
		i++;
	}
	split[i] = NULL;
	return (split);
}