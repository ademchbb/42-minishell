/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:33 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/04 15:10:52 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "env.h"

t_env	*new_env_node(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*eq_pos;
	char	*name;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			name = ft_substr(envp[i], 0, eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			if (!name || !value)
				return (free(name), free(value), free_env(env), NULL);
			add_back_env(&env, new_env_node(name, value));
		}
		i++;
	}
	return (env);
}
