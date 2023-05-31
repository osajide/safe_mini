/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:44:57 by osajide           #+#    #+#             */
/*   Updated: 2023/05/31 19:34:28 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	look_for_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remove_char(char *s, int ascii)
{
	char	*new_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ascii)
			j++;
		i++;
	}
	new_char = malloc((i - j) + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ascii)
			i++;
		else
			new_char[j++] = s[i++];
	}
	new_char[j] = '\0';
	free(s);
	return (new_char);
}

void	check_inside_double_quotes(char *temp, char *line, t_list **lst, int *pos)
{
	int		start;
	char	*temp1;
	
	temp1 = NULL;
	start = *pos;
	(*pos)++;
	while (line[*pos] && line[*pos] != 34)
		(*pos)++;
	temp1 = ft_substr(line, start, *pos + 1);
	if (look_for_char(temp1))
	{
		ft_lstadd_back(lst, ft_lstnew(temp, NOTHING, WORD));
		ft_lstadd_back(lst, ft_lstnew(temp1, IN_DQ, WORD));
	}
	else
	{
		temp1 = ft_remove_char(temp1, 34);
		ft_lstadd_back(lst, ft_lstnew(ft_strjoin(temp, temp1), NOTHING, WORD));
	}
}

char	*handle_quote(t_list **lst, char *line, int *pos, int ascii)
{
	char	*temp;
	int		start;

	(*pos)++;
	start = *pos;
	while (line[*pos] && line[*pos] != ascii)
		(*pos)++;
	temp = ft_substr(line, start, *pos);
	return (temp);
}

void	skip_inside_quotes(char *line, int *pos, int ascii)
{
	(*pos)++;
	while (line[*pos] && line[*pos] != ascii)
		(*pos)++;
}

void	if_string(char *line, t_list **lst, int *pos)
{
	int		start;
	char	*temp;

	temp = NULL;
	start = *pos;
	while (line[*pos] && line[*pos] != ' ' && line[*pos] != '<' && line[*pos] != '>' && line[*pos] != '|')
	{
		if (line[*pos] == 34)
			skip_inside_quotes(line, pos, 34);
		else if (line[*pos] == 39)
			skip_inside_quotes(line, pos, 39);
		(*pos)++;
	}
	(*pos)--;
	temp = ft_substr(line, start, *pos + 1);
	ft_lstadd_back(lst, ft_lstnew(temp, NOTHING, WORD));
}

void	if_single_quote(char *line, t_list **lst, int *pos)
{
	char	*temp;
	char	*temp2;
	int		start;

	temp = NULL;
	temp2 = NULL;
	temp = handle_quote(lst, line, pos, 39);
	(*pos)++;
	start = *pos;
	while (line[*pos] && line[*pos]!= '$' && line[*pos] != '|' && line[*pos] != '<' && line[*pos] != '>' && line[*pos] != ' ')
		(*pos)++;
	temp2 = ft_strjoin(temp, ft_substr(line, start, *pos));
	if (temp2 && *temp2)
		ft_lstadd_back(lst, ft_lstnew(ft_remove_char(temp2, 39), IN_SQ, WORD));
}

void	if_double_quote(char *line, t_list **lst, int *pos)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		start;

	temp = NULL;
	start = *pos;
	(*pos)++;
	while (line[*pos] && line[*pos] != 34)
		(*pos)++;
	temp = ft_substr(line, start, *pos + 1);
	printf("temp in double quote = %s\n", temp);
	(*pos)++;
	if (line[*pos] && line[*pos] != ' ')
	{
		printf("line[%d] = %c\n", *pos, line[*pos]);
		start = *pos;
		(*pos)++;
		while (line[*pos] && line[*pos] != '|' && line[*pos] != '<' && line[*pos] != '>' && line[*pos] != ' ')
			(*pos)++;
		temp2 = ft_substr(line, start, *pos + 1);
		temp3 = ft_strjoin(temp, temp2);
		if (temp3 && *temp3)
			ft_lstadd_back(lst, ft_lstnew(ft_remove_char(temp3, 0), NOTHING, WORD));
	}
	else
	{
		temp = ft_remove_char(temp, 34);
		ft_lstadd_back(lst, ft_lstnew(temp, IN_DQ, WORD));
	}
}
