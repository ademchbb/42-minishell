/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:14:05 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/13 06:55:02 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	exec_child(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	path = resolve_path(cmd->args[0], env);
	if (!path)
	{
		err_msg(cmd->args[0], "command not found");
		exit(127);
	}
	envp = env_to_array(env);
	execve(path, cmd->args, envp);
	err_msg(cmd->args[0], strerror(errno));
	exit(126);
}
