/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:06:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/02 17:03:46 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_pipes(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	while (str[++i])
	{	
		count = 0;
		if (str[i] == c)
		{
			while (str[i++] == c)
				count++;
			if (count == 3)
			{
				printf("minishell: syntax error near unexpected token `%c'\n", c);
				return (0);
			}
			else if (count > 3)
			{
				printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
				return (0);
			}
		}
	}
	return (1);
}

int	number_of_quotes(char *line, int ascii)
{
	int	i;
	int	number_of_quotes;

	i = 0;
	number_of_quotes = 0;
	while (line[i])
	{
		if (line[i] == ascii)
			number_of_quotes++;
		i++;
	}
	return (number_of_quotes);
}

int	next_quote(char *line, int *i, int ascii)
{
	int	count;

	count = 1;
	while (line[*i])
	{
		if (line[*i] == ascii)
			return (count++, count);
		(*i)++;
	}
	return (count);
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != 34 && line[i] != 39)
		i++;
	if (!line[i])
		return (1);
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			if (next_quote(line, &i, 34) == 1)
				return (ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2), 0);
		}
		else if (line[i] == 39)
		{
			i++;
			if (next_quote(line, &i, 39) == 1)
				return (ft_putstr_fd("\n\n\nminishell: syntax error !!!!\n\n\n", 2), 0);
		}
		i++;
	}
	return (1);
}

void	check_input(char *line)
{
	if (!check_quotes(line))
		return ;
	if (!check_pipes(line, '|'))
		return ;
	if (!check_pipes(line, '&'))
		return ;
	if (!check_pipes(line, '>'))
		return ;
	if (!check_pipes(line, '<'))
		return ;
}
