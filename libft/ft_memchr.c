/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:22:16 by adchebbi          #+#    #+#             */
/*   Updated: 2025/11/18 13:08:53 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*str;
	size_t				i;

	i = 0;
	str = (unsigned const char *) s;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}
