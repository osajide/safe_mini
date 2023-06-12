/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:07:48 by osajide           #+#    #+#             */
/*   Updated: 2022/11/01 12:57:33 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_lowerhexa(unsigned int n)
{
	int		count;
	char	*hex;

	hex = "0123456789abcdef";
	count = 0;
	if (n < 16)
		count = ft_putchar(hex[n]);
	else
	{
		count = ft_lowerhexa((n / 16));
		count += ft_lowerhexa((n % 16));
	}
	return (count);
}
