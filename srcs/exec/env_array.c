/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 06:36:30 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/15 19:32:04 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_env(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static char	*join_entry(t_env *env)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(env->name, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, env->value);
	free(tmp);
	return (entry);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = join_entry(env);
		if (!arr[i])
		{
			while (--i >= 0)
				free(arr[i]);
			return (free(arr), NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
