/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:09:10 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 19:54:43 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s2;
	size_t		i;
	size_t		len_s1;

	if (!s1)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	s2 = malloc(len_s1 + 1);
	if (!s2)
		return (NULL);
	while (i < len_s1)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
