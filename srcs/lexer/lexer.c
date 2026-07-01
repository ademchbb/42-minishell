/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:04:43 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 14:19:59 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(char *word, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = word;
	new->type = type;
	new->quoted = 0;
	new->next = NULL;
	return (new);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*define_token_type(char *str)
{
	t_token	*tok;

	if (ft_strcmp(str, "|") == 0)
		return (new_token(str, PIPE));
	if (ft_strcmp(str, ">") == 0)
		return (new_token(str, RED_OUT));
	if (ft_strcmp(str, "<") == 0)
		return (new_token(str, RED_IN));
	if (ft_strcmp(str, "<<") == 0)
		return (new_token(str, READ_IN));
	if (ft_strcmp(str, ">>") == 0)
		return (new_token(str, READ_OUT));
	tok = new_token(str, WORD);
	if (tok)
		tok->quoted = (ft_strchr(str, '\'') != NULL
				|| ft_strchr(str, '"') != NULL);
	return (tok);
}

t_token	*lexer(char **split_res)
{
	t_token	*word;
	t_token	*token;
	int		i;

	i = 0;
	if (!split_res)
	{
		perror("Error");
		return (NULL);
	}
	token = NULL;
	while (split_res[i])
	{
		word = define_token_type(split_res[i]);
		add_back_token(&token, word);
		i++;
	}
	return (token);
}

void	clear_token(t_token **lst)
{
	t_token	*curr;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		free(curr->token);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
