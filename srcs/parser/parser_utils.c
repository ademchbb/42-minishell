/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 06:25:01 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 13:57:45 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	args_count(t_cmd *c)
{
	int	n;

	n = 0;
	while (c->args && c->args[n])
		n++;
	return (n);
}

int	push_arg(t_cmd *c, char *value)
{
	int		n;
	char	**arr;
	int		i;

	n = args_count(c);
	arr = malloc(sizeof(char *) * (n + 2));
	if (!arr)
		return (1);
	i = 0;
	while (i < n)
	{
		arr[i] = c->args[i];
		i++;
	}
	arr[n] = value;
	arr[n + 1] = NULL;
	free(c->args);
	c->args = arr;
	return (0);
}

static int	push_redir(t_cmd *c, t_redir_type t, char *target, int quoted)
{
	t_redir	*r;
	t_redir	*cur;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (1);
	r->type = t;
	r->target = target;
	r->heredoc_fd = -1;
	r->quoted = quoted;
	r->next = NULL;
	if (!c->redirs)
		return (c->redirs = r, 0);
	cur = c->redirs;
	while (cur->next)
		cur = cur->next;
	cur->next = r;
	return (0);
}

int	handle_redir(t_token **tok, t_cmd *cur)
{
	t_token			*op;
	t_token			*tgt;
	t_redir_type	rt;

	op = *tok;
	tgt = op->next;
	if (!tgt || tgt->type != WORD)
		return (err_msg("syntax error", "expected filename"), 2);
	if (op->type == RED_IN)
		rt = R_IN;
	else if (op->type == RED_OUT)
		rt = R_OUT;
	else if (op->type == READ_OUT)
		rt = R_APPEND;
	else
		rt = R_HEREDOC;
	if (push_redir(cur, rt, ft_strdup(tgt->token), tgt->quoted))
		return (1);
	*tok = tgt->next;
	return (0);
}
