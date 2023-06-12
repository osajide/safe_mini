/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upperhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:17:37 by osajide           #+#    #+#             */
/*   Updated: 2022/11/01 12:57:22 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_upperhexa(unsigned int n)
{
	int		count;
	char	*hex;

	hex = "0123456789ABCDEF";
	count = 0;
	if (n < 16)
		count = ft_putchar(hex[n]);
	else
	{
		count = ft_upperhexa((n / 16));
		count += ft_upperhexa((n % 16));
	}
	return (count);
}
