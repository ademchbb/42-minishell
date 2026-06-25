/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:17:21 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/25 18:01:11 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

extern int	g_status;

static int	open_redir(t_redir *r)
{
	if (r->type == R_IN)
		return (open(r->target, O_RDONLY));
	if (r->type == R_OUT)
		return (open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == R_APPEND)
		return (open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (r->type == R_HEREDOC)
		return (handle_heredoc(r->target));
	return (-2);
}

int	apply_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		fd = open_redir(r);
		if (fd == -3)
			return (1);
		if (fd == -1)
			return (err_msg(r->target, strerror(errno)), 1);
		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		if (fd >= 0)
			close(fd);
		r = r->next;
	}
	return (0);
}
