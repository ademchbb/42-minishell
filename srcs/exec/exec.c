/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 05:54:29 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/13 06:56:37 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fds)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
	}
	if (apply_redirs(cmd->redirs))
		exit(1);
	exec_child(cmd, env);
}

static int	spawn_one(t_cmd *cmd, t_env *env, int *prev_fd)
{
	int		fds[2];
	pid_t	pid;

	if (cmd->next && pipe(fds) == -1)
		return (err_msg("pipe", strerror(errno)), -1);
	pid = fork();
	if (pid == -1)
		return (err_msg("fork", strerror(errno)), -1);
	if (pid == 0)
		child_process(cmd, env, *prev_fd, fds);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fds[1]);
		*prev_fd = fds[0];
	}
	else
		*prev_fd = -1;
	return (pid);
}

static int	wait_all(pid_t last_pid)
{
	int		status;
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid && WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (pid == last_pid && WIFSIGNALED(status))
			ret = 128 + WTERMSIG(status);
		pid = wait(&status);
	}
	return (ret);
}

int	exec_cmds(t_cmd *cmds, t_env *env)
{
	int		prev_fd;
	pid_t	last;

	prev_fd = -1;
	last = -1;
	while (cmds)
	{
		last = spawn_one(cmds, env, &prev_fd);
		if (last == -1)
			return (1);
		cmds = cmds->next;
	}
	return (wait_all(last));
}
