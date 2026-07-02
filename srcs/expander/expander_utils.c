/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 21:26:23 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 19:54:45 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env_val(t_env *env, char *name)
{
	t_env	*current;

	if (!env || !name)
		return (ft_strdup(""));
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (!current->value)
				return (ft_strdup(""));
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

int	get_name_len(char *str, int start)
{
	int	len;

	len = 0;
	if (str[start] == '?')
		return (1);
	while (str[start + len] && (ft_isalnum(str[start + len])
			|| str[start + len] == '_'))
		len++;
	return (len);
}

char	*assemble_str(char *before, char *variable_value, char *after)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(before, variable_value);
	if (!tmp)
		return (free(before), free(variable_value),
			free(after), NULL);
	res = ft_strjoin(tmp, after);
	free(tmp);
	free(before);
	free(variable_value);
	free(after);
	return (res);
}

char	*replace_variable(char *old_str, int dollar,
	t_env *env, int error_status)
{
	char	*before;
	char	*name;
	char	*variable_value;
	char	*after;
	int		name_len;

	before = ft_substr(old_str, 0, dollar);
	name_len = get_name_len(old_str, dollar + 1);
	name = ft_substr(old_str, dollar + 1, name_len);
	if (name && ft_strcmp(name, "?") == 0)
		variable_value = ft_itoa(error_status);
	else
		variable_value = get_env_val(env, name);
	free(name);
	after = ft_strdup(old_str + dollar + 1 + name_len);
	if (!before || !variable_value || !after)
		return (free(before), free(variable_value),
			free(after), old_str);
	free(old_str);
	return (assemble_str(before, variable_value, after));
}
