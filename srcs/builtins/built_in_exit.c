/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 18:49:08 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/01 22:41:03 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	str_to_long(char *s, int *ok)
{
	unsigned long long	acc;
	int					i;
	int					sign;

	acc = 0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		acc = acc * 10 + (s[i] - '0');
		if ((sign == 1 && acc > 9223372036854775807ULL)
			|| (sign == -1 && acc > 9223372036854775807ULL))
			*ok = 0;
		i++;
	}
	if (sign == -1)
		return (-(long)acc);
	return ((long)acc);
}

static void	exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	exit_cleanup(t_cmd *cmd, t_env **env)
{
	free_env(*env);
	cmds_free(cmd);
	rl_clear_history();
}

int	builtin_exit(t_cmd *cmd, t_env **env, int last_status)
{
	int		ok;
	long	code;

	if (!cmd->args[1])
	{
		exit_cleanup(cmd, env);
		exit((unsigned char)last_status);
	}
	ok = 1;
	code = str_to_long(cmd->args[1], &ok);
	if (!is_valid_num(cmd->args[1]) || !ok)
	{
		exit_error(cmd->args[1]);
		exit_cleanup(cmd, env);
		exit(2);
	}
	if (cmd->args[2])
		return (err_msg("exit", "too many arguments"), 1);
	exit_cleanup(cmd, env);
	exit((unsigned char)(code % 256));
}
