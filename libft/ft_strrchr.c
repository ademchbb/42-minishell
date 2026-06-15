/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:02:06 by adchebbi          #+#    #+#             */
/*   Updated: 2025/11/16 17:08:25 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len_s;

	len_s = ft_strlen(s);
	if ((char) c == '\0')
		return ((char *)s + len_s);
	while (len_s >= 0)
	{
		if ((unsigned char) c == s[len_s])
			return ((char *)s + len_s);
		len_s--;
	}
	return (NULL);
}
