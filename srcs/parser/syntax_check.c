/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 20:50:31 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/18 22:28:26 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	if (in_squote || in_dquote)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

int	check_tokens_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == RED_IN || curr->type == RED_OUT
			|| curr->type == READ_IN || curr->type == READ_OUT)
		{
			if (!curr->next)
			{
				printf("minishell: syntax error: expected filename\n");
				return (1);
			}
			else if (curr->next->type != WORD)
			{
				printf("minishell: syntax error: unexpected token\n");
			}
		}
		curr = curr->next;
	}
	return (0);
}
