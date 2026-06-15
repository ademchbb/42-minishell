/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:40:51 by adchebbi          #+#    #+#             */
/*   Updated: 2026/01/21 11:23:12 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_unsigned(n / 10);
	count += ft_print_char('0' + (n % 10));
	return (count);
}

int	ft_print_hex(unsigned int n, int uppercase)
{
	int				count;
	unsigned int	digit;

	count = 0;
	if (n >= 16)
		count += ft_print_hex(n / 16, uppercase);
	digit = n % 16;
	if (digit < 10)
		count += ft_print_char('0' + digit);
	else
	{
		if (uppercase)
			count += ft_print_char('A' + (digit - 10));
		else
			count += ft_print_char('a' + (digit - 10));
	}
	return (count);
}

static int	ft_print_hex_unlg(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_print_hex_unlg(n / 16);
	count += ft_print_char("0123456789abcdef"[n % 16]);
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	unsigned long		addr;
	int					count;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	addr = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	count = 2;
	count += ft_print_hex_unlg(addr);
	return (count);
}
