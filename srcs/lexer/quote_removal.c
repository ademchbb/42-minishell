/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 23:05:51 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/18 10:21:05 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_cleanstr_len(char *str)
{
	int	i;
	int	len;
	int	in_squote;
	int	in_dquote;

	i = 0;
	len = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else
			len++;
		i++;
	}
	return (len);
}

static void	copy_without_quotes(char *src, char *dst)
{
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (src && src[i])
	{
		if (src[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (src[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

static void	remove_token_quotes(t_token *tok)
{
	char	*clean_str;

	if (!tok || !tok->token)
		return ;
	clean_str = malloc(sizeof(char) * (get_cleanstr_len(tok->token) + 1));
	if (!clean_str)
		return ;
	copy_without_quotes(tok->token, clean_str);
	free(tok->token);
	tok->token = clean_str;
}

void	quote_removal(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
			remove_token_quotes(current);
		current = current->next;
	}
}
