/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:14:05 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 13:08:18 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	exec_child(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, &env, 0));
	path = resolve_path(cmd->args[0], env);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], F_OK) == 0)
		{
			err_msg(cmd->args[0], "Permission denied");
			exit(126);
		}
		err_msg(cmd->args[0], "command not found");
		exit(127);
	}
	envp = env_to_array(env);
	execve(path, cmd->args, envp);
	err_msg(cmd->args[0], strerror(errno));
	exit(126);
}
