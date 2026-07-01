/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 05:58:09 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 06:36:13 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static char	*key_part(char *arg, char *eq)
{
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

static int	export_one(t_env **env, char *arg)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(arg, '=');
	name = key_part(arg, eq);
	if (!name)
		return (1);
	if (!valid_key(name))
		return (free(name), export_error(arg));
	if (eq)
		env_set(env, name, eq + 1);
	else if (!env_find(*env, name))
		env_set(env, name, NULL);
	free(name);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (export_print(*env), 0);
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (export_one(env, cmd->args[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
