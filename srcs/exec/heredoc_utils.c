/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:53:53 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 14:21:29 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_delimiter(char *line, char *delimiter)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (ft_strlen(delimiter) == len && ft_strncmp(line, delimiter,
			len) == 0);
}

int	run_heredocs_pre_exec(t_cmd *cmds, t_env *env)
{
	t_cmd	*c;
	t_redir	*r;

	c = cmds;
	while (c)
	{
		r = c->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				r->heredoc_fd = handle_heredoc(r->target, env, r->quoted);
				if (r->heredoc_fd == -3)
					return (130);
			}
			r = r->next;
		}
		c = c->next;
	}
	return (0);
}
