/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:57:59 by adchebbi          #+#    #+#             */
/*   Updated: 2026/01/23 09:16:11 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	if (!dst && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *) dst;
	s = (unsigned const char *) src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
