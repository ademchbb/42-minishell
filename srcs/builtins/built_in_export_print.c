/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 06:05:08 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 07:28:42 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	count_nodes(t_env *env)
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

static t_env	**collect_nodes(t_env *env)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * (count_nodes(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_nodes(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_node(t_env *e)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(e->name, 1);
	if (e->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(e->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}

void	export_print(t_env *env)
{
	t_env	**arr;
	int		i;

	arr = collect_nodes(env);
	if (!arr)
		return ;
	sort_nodes(arr, count_nodes(env));
	i = 0;
	while (arr[i])
		print_node(arr[i++]);
	free(arr);
}
