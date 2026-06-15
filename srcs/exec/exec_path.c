/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:27:07 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/13 06:55:05 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*env_get_value(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*try_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (full && access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*found;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		found = try_dir(paths[i], cmd);
		if (found)
			return (found);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;
	char	*found;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_value = env_get_value(env, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	found = search_in_paths(paths, cmd);
	free_tab(paths);
	return (found);
}
