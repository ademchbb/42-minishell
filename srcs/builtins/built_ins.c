/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:34:09 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 06:33:40 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

int	is_single_builtin(t_cmd *cmd)
{
	if (cmd->next || !cmd->args || !cmd->args[0])
		return (0);
	return (is_builtin(cmd->args[0]));
}

int	run_builtin(t_cmd *cmd, t_env **env, int last_status)
{
	char	*name;

	name = cmd->args[0];
	if (!ft_strcmp(name, "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(name, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(name, "env"))
		return (builtin_env(*env));
	if (!ft_strcmp(name, "cd"))
		return (builtin_cd(cmd, env));
	if (!ft_strcmp(name, "export"))
		return (builtin_export(cmd, env));
	if (!ft_strcmp(name, "unset"))
		return (builtin_unset(cmd, env));
	return (builtin_exit(cmd, env, last_status));
}

static void	restore_fds(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(in_fd);
	close(out_fd);
}

int	run_builtin_parent(t_cmd *cmd, t_env **env, int last_status)
{
	int	in_fd;
	int	out_fd;
	int	status;

	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs))
	{
		restore_fds(in_fd, out_fd);
		return (1);
	}
	if (!ft_strcmp(cmd->args[0], "exit"))
		ft_putendl_fd("exit", 2);
	status = run_builtin(cmd, env, last_status);
	restore_fds(in_fd, out_fd);
	return (status);
}
