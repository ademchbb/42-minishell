/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:31:33 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/10 18:32:28 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	update_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '\"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

static int	count_words(char const *s)
{
	int	i;
	int	count;
	int	in_squote;
	int	in_dquote;

	i = 0;
	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i])
			count++;
		while (s[i] && (s[i] != ' ' || in_squote || in_dquote))
		{
			update_quotes(s[i], &in_squote, &in_dquote);
			i++;
		}
	}
	return (count);
}

static int	get_word_len(char const *s, int start)
{
	int	len;
	int	in_squote;
	int	in_dquote;

	len = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[start + len] && (s[start + len] != ' ' || in_squote || in_dquote))
	{
		update_quotes(s[start + len], &in_squote, &in_dquote);
		len++;
	}
	return (len);
}

static void	free_split(char **arr, int j)
{
	while (j > 0)
		free(arr[--j]);
	free(arr);
}

char	**ms_split(char const *s)
{
	char	**arr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		arr[j] = ft_substr(s, i, get_word_len(s, i));
		if (!arr[j])
			return (free_split(arr, j), NULL);
		i += ft_strlen(arr[j++]);
	}
	arr[j] = NULL;
	return (arr);
}
