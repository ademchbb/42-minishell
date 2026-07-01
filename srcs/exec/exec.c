/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 05:54:29 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 14:08:56 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

static void	child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fds)
{
	init_signals_child();
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
	{
		if (g_status == 130)
			exit(130);
		exit(1);
	}
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

static void	check_child_status(int status, pid_t pid, pid_t last_pid, int *ret)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT && pid == last_pid)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT && pid == last_pid)
			write(1, "Quit (core dumped)\n", 19);
		if (pid == last_pid)
			*ret = 128 + WTERMSIG(status);
	}
	else if (pid == last_pid && WIFEXITED(status))
	{
		*ret = WEXITSTATUS(status);
		if (*ret == 130)
			g_status = 130;
	}
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
		check_child_status(status, pid, last_pid, &ret);
		pid = wait(&status);
	}
	return (ret);
}

int	exec_cmds(t_cmd *cmds, t_env **env, int last_status)
{
	int		prev_fd;
	pid_t	last;
	int		ret;

	if (run_heredocs_pre_exec(cmds, *env) == 130)
	{
		g_status = 130;
		return (130);
	}
	if (is_single_builtin(cmds))
		return (run_builtin_parent(cmds, env, last_status));
	prev_fd = -1;
	last = -1;
	init_signals_parent();
	while (cmds)
	{
		last = spawn_one(cmds, *env, &prev_fd);
		if (last == -1)
			return (init_signals(), 1);
		cmds = cmds->next;
	}
	ret = wait_all(last);
	init_signals();
	return (ret);
}
