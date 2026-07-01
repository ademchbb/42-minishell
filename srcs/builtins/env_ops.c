/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:12:33 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 06:36:44 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*env_find(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	env_append(t_env **env, char *name, char *value)
{
	char	*namedup;
	t_env	*node;

	namedup = ft_strdup(name);
	if (!namedup)
		return (free(value), 1);
	node = new_env_node(namedup, value);
	if (!node)
		return (free(namedup), free(value), 1);
	add_back_env(env, node);
	return (0);
}

int	env_set(t_env **env, char *name, char *value)
{
	t_env	*node;
	char	*dup;

	dup = NULL;
	if (value)
	{
		dup = ft_strdup(value);
		if (!dup)
			return (1);
	}
	node = env_find(*env, name);
	if (node)
	{
		free(node->value);
		node->value = dup;
		return (0);
	}
	return (env_append(env, name, dup));
}

int	valid_key(char *key)
{
	int	i;

	if (!key || !key[0] || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_unset(t_env **env, char *name)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			return (free(cur->name), free(cur->value), free(cur), 0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
