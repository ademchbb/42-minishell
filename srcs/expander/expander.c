/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 22:30:54 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/30 18:31:40 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_token_content(t_token *tok, t_env *env, int error_status)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (tok->token && tok->token[i])
	{
		if (tok->token[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (tok->token[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (tok->token[i] == '$' && !in_squote)
		{
			if (tok->token[i + 1] && (ft_isalnum(tok->token[i + 1])
					|| tok->token[i + 1] == '_' || tok->token[i + 1] == '?'))
			{
				tok->token = replace_variable(tok->token, i, env, error_status);
				i--;
			}
		}
		i++;
	}
}

void	expander(t_token *tokens, t_env *env, int error_status)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
			expand_token_content(current, env, error_status);
		current = current->next;
	}
}

char	*expand_heredoc_line(char *line, t_env *env, int error_status)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] && (ft_isalnum(line[i + 1])
					|| line[i + 1] == '_' || line[i + 1] == '?'))
			{
				line = replace_variable(line, i, env, error_status);
				i--;
			}
		}
		i++;
	}
	return (line);
}
