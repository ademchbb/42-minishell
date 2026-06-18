/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 20:57:31 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/18 22:34:20 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	check_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
	else if (c == '\"' && !*in_squote)
		*in_dquote = !*in_dquote;
}

static int	get_line_len(char *line)
{
	int	i;
	int	len;
	int	in_squote;
	int	in_dquote;

	i = -1;
	len = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line && line[++i])
	{
		check_quotes(line[i], &in_squote, &in_dquote);
		if (!in_squote && !in_dquote && is_op(line[i]))
		{
			if (i > 0 && line[i - 1] != ' '
				&& (!is_op(line[i - 1]) || line[i - 1] != line[i]))
				len++;
			if (line[i + 1] && line[i + 1] != ' ' && (!is_op(line[i + 1])
					|| line[i + 1] != line[i]
					|| (i > 0 && line[i - 1] == line[i])))
				len++;
		}
		len++;
	}
	return (len);
}

static void	copy_w_spaces(char *src, char *dst, int i, int j)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (src && src[i])
	{
		check_quotes(src[i], &in_squote, &in_dquote);
		if (!in_squote && !in_dquote && is_op(src[i]))
		{
			if (i > 0 && src[i - 1] != ' '
				&& (!is_op(src[i - 1]) || src[i - 1] != src[i]))
				dst[j++] = ' ';
			dst[j++] = src[i];
			if (src[i + 1] && src[i + 1] != ' ' && (!is_op(src[i + 1])
					|| src[i + 1] != src[i] || (i > 0 && src[i - 1] == src[i])))
				dst[j++] = ' ';
			i++;
			continue ;
		}
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
}

char	*add_spaces_ops(char *line)
{
	char	*new_line;
	int		new_len;

	if (!line)
		return (NULL);
	new_len = get_line_len(line);
	new_line = malloc(sizeof(char) * (new_len + 1));
	if (!new_line)
		return (NULL);
	copy_w_spaces(line, new_line, 0, 0);
	return (new_line);
}
