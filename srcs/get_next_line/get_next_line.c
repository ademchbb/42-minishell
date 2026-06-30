/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:15:57 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/30 15:07:29 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*add_content_buff(char *stash, char *buffer)
{
	char	*combined;

	if (!stash)
		stash = ft_strdup("");
	if (!stash || !buffer)
		return (NULL);
	combined = ft_strjoin(stash, buffer);
	free(stash);
	return (combined);
}

static char	*extract_line(char **storage)
{
	char	*line;
	char	*residue;
	int		i;

	if (!*storage || !**storage)
		return (NULL);
	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
	{
		line = ft_substr(*storage, 0, i + 1);
		residue = ft_strdup(*storage + i + 1);
		free(*storage);
		*storage = residue;
		return (line);
	}
	line = ft_strdup(*storage);
	free(*storage);
	*storage = NULL;
	return (line);
}

static char	*load_data(int fd, char *storage)
{
	char	*tmp_buf;
	int		ret;

	tmp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buf)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, tmp_buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(tmp_buf);
			free(storage);
			return (NULL);
		}
		tmp_buf[ret] = '\0';
		storage = add_content_buff(storage, tmp_buf);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(tmp_buf);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = load_data(fd, backup);
	if (!backup)
		return (NULL);
	line = extract_line(&backup);
	if (!line && backup)
	{
		free(backup);
		backup = NULL;
	}
	return (line);
}
