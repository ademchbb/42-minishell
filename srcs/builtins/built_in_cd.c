/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:58:59 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 22:40:51 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static char	*cd_special(t_env *env, char*name)
{
	char	*val;

	val = env_get_value(env, name);
	if (val)
		return (val);
	if (!strcmp(name, "HOME"))
		err_msg("cd", "HOME not set");
	else
		err_msg("cd", "OLDPWD not set");
	return (NULL);
}

static char	*get_cd_target(t_cmd *cmd, t_env *env)
{
	char	*arg;
	char	*val;

	arg = cmd->args[1];
	if (!arg || !ft_strcmp(arg, "~"))
		return (cd_special(env, "HOME"));
	if (!ft_strcmp(arg, "-"))
	{
		val = cd_special(env, "OLDPWD");
		if (val)
			ft_putendl_fd(val, 1);
		return (val);
	}
	return (arg);
}

static void	update_pwd(t_env **env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (oldpwd)
		env_set(env, "OLDPWD", oldpwd);
	if (newpwd)
		env_set(env, "PWD", newpwd);
	free(newpwd);
}

int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	*target;
	char	*oldpwd;

	if (cmd->args[1] && cmd->args[2])
		return (err_msg("cd", "too many arguments"), 1);
	target = get_cd_target(cmd, *env);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
		return (free(oldpwd), cd_error(target));
	update_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
