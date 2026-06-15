/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:17:21 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/13 06:58:04 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_redir(t_redir *r)
{
	if (r->type == R_IN)
		return (open(r->target, O_RDONLY));
	if (r->type == R_OUT)
		return (open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == R_APPEND)
		return (open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-2);
}

int	apply_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		fd = open_redir(r);
		if (fd == -2)
			return (err_msg("heredoc", "pas encore implemente"), 1);
		if (fd == -1)
			return (err_msg(r->target, strerror(errno)), 1);
		if (r->type == R_IN)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		close(fd);
		r = r->next;
	}
	return (0);
}
/* TODO Modifier lorsqu on fera heredoc le premier if */
