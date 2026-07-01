/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 06:18:08 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 06:20:48 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (!valid_key(cmd->args[i]))
			ret = unset_error(cmd->args[i]);
		else
			env_unset(env, cmd->args[i]);
		i++;
	}
	return (ret);
}
