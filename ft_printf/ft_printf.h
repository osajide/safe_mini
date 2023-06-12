/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:20:30 by osajide           #+#    #+#             */
/*   Updated: 2022/10/31 10:22:52 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<unistd.h>
# include<stdarg.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_unputnbr(unsigned int n);
int	ft_upperhexa(unsigned int n);
int	ft_lowerhexa(unsigned int n);
int	ft_pointer(unsigned long n);
int	ft_printf(const char *s, ...);
#endif
