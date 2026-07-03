/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:26:46 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/03 21:04:42 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_verify(char *tmp, char *buff)
{
	char	*keep_tmp;
	int		len;

	len = 0;
	keep_tmp = NULL;
	if (tmp)
	{
		keep_tmp = ft_strdup(tmp);
		free(tmp);
		len = ft_strlen(keep_tmp) + ft_strlen(buff);
		tmp = (char *)malloc(len + 1);
		if (!tmp)
		{
			free(keep_tmp);
			return (NULL);
		}
		ft_memcpy(tmp, keep_tmp, ft_strlen(keep_tmp) + 1);
		tmp[ft_strlen(keep_tmp)] = '\0';
		ft_memcpy(ft_strchr(tmp, '\0'), buff, ft_strlen(buff));
		tmp[len] = '\0';
		free(keep_tmp);
	}
	else if (!tmp)
		tmp = ft_strdup(buff);
	return (tmp);
}

void	ft_extract(char **ptr)
{
	char	*keep_tmp;
	char	*newline_pos;

	newline_pos = ft_strchr(*ptr, '\n');
	if (newline_pos && *(newline_pos + 1))
	{
		keep_tmp = ft_strdup(newline_pos + 1);
		free(*ptr);
		*ptr = keep_tmp;
	}
	else
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_free(char **ptr_tmp, char **ptr_buff, ssize_t rb)
{
	char	*line;

	line = NULL;
	if (*ptr_tmp && **ptr_tmp && rb == 0)
	{
		line = ft_strdup(*ptr_tmp);
		free(*ptr_tmp);
		*ptr_tmp = NULL;
		free(*ptr_buff);
		*ptr_buff = NULL;
		return (line);
	}
	if (*ptr_tmp && ft_strchr(*ptr_tmp, '\n') != NULL)
	{
		line = ft_substr(*ptr_tmp, 0, (ft_strlen(*ptr_tmp)
					- ft_strlen(ft_strchr(*ptr_tmp, '\n'))) + 1);
		ft_extract(ptr_tmp);
		return (line);
	}
	free(*ptr_tmp);
	*ptr_tmp = NULL;
	free(*ptr_buff);
	*ptr_buff = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buff;
	ssize_t		read_bytes;

	buff = NULL;
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (read_bytes != 0)
	{
		if (tmp && (ft_strchr(tmp, '\n') != NULL))
			return (ft_free(&tmp, &buff, read_bytes));
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff[read_bytes] = '\0';
		tmp = ft_verify(tmp, buff);
		free(buff);
		buff = NULL;
	}
	return (ft_free(&tmp, &buff, read_bytes));
}
