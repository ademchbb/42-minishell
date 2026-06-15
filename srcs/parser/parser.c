/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 06:25:20 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/10 11:09:31 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*c;

	c = malloc(sizeof(t_cmd));
	if (!c)
		return (NULL);
	c->args = NULL;
	c->redirs = NULL;
	c->next = NULL;
	return (c);
}

static int	handle_word(t_token **tok, t_cmd *cur)
{
	if (push_arg(cur, ft_strdup((*tok)->token)))
		return (1);
	*tok = (*tok)->next;
	return (0);
}

static int	handle_pipe(t_token **tok, t_cmd **cur)
{
	t_cmd	*new;

	if (!(*cur)->args && !(*cur)->redirs)
		return (err_msg("syntax error", "unexpected '|'"), 2);
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type == PIPE)
		return (err_msg("syntax error", "unexpected '|'"), 2);
	new = new_cmd();
	if (!new)
		return (1);
	(*cur)->next = new;
	*cur = new;
	return (0);
}

t_cmd	*parse(t_token *toks, int *err_status)
{
	t_cmd	*head;
	t_cmd	*cur;
	int		rc;

	head = new_cmd();
	if (!head)
		return (NULL);
	cur = head;
	while (toks)
	{
		if (toks->type == WORD)
			rc = handle_word(&toks, cur);
		else if (toks->type == PIPE)
			rc = handle_pipe(&toks, &cur);
		else
			rc = handle_redir(&toks, cur);
		if (rc != 0)
			return (*err_status = rc, cmds_free(head), NULL);
	}
	return (head);
}
