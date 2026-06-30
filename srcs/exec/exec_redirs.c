/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:17:21 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/30 17:57:17 by ragolden         ###   ########.fr       */
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
		return (r->heredoc_fd);
	return (-2);
}

static void	update_redir_fd(t_redir *r, int fd, int *last_in, int *last_out)
{
	if (r->type == R_IN || r->type == R_HEREDOC)
	{
		if (*last_in >= 0)
			close(*last_in);
		*last_in = fd;
	}
	else
	{
		if (*last_out >= 0)
			close(*last_out);
		*last_out = fd;
	}
}

static void	finalize_redirs(int last_in, int last_out)
{
	if (last_in >= 0)
	{
		dup2(last_in, 0);
		close(last_in);
	}
	if (last_out >= 0)
	{
		dup2(last_out, 1);
		close(last_out);
	}
}

int	apply_redirs(t_redir *r)
{
	int	fd;
	int	last_in;
	int	last_out;

	last_in = -1;
	last_out = -1;
	while (r)
	{
		fd = open_redir(r);
		if (fd == -3)
			return (1);
		if (fd == -1)
			return (err_msg(r->target, strerror(errno)), 1);
		update_redir_fd(r, fd, &last_in, &last_out);
		r = r->next;
	}
	finalize_redirs(last_in, last_out);
	return (0);
}
