/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:07 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 20:52:13 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "signals.h"

int				g_status = 0;

static void	check_g_status(int *error_status)
{
	if (g_status == 130)
	{
		*error_status = g_status;
		g_status = 0;
	}
}

static t_token	*tokenize(char *line)
{
	char	**split_res;
	t_token	*tokens;

	line = add_spaces_ops(line);
	if (!line)
		return (NULL);
	split_res = ms_split(line);
	free(line);
	if (!split_res)
		return (NULL);
	tokens = lexer(split_res);
	free(split_res);
	return (tokens);
}

static void	line_process(char *line, t_env **env_list, int *error_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line);
	if (!tokens)
		return ;
	if (check_tokens_syntax(tokens))
	{
		*error_status = 2;
		clear_token(&tokens);
		return ;
	}
	expander(&tokens, *env_list, *error_status);
	quote_removal(tokens);
	cmds = parse(tokens, error_status);
	clear_token(&tokens);
	if (!cmds)
		return ;
	*error_status = exec_cmds(cmds, env_list, *error_status);
	cmds_free(cmds);
}

static void	shell_simu_loop(t_env **env_list, int *error_status)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		check_g_status(error_status);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (check_unclosed_quotes(line))
		{
			*error_status = 2;
			free(line);
			continue ;
		}
		line_process(line, env_list, error_status);
		check_g_status(error_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int		error_status;

	(void)ac;
	(void)av;
	error_status = 0;
	env_list = init_env(envp);
	if (!env_list)
		return (1);
	init_signals();
	shell_simu_loop(&env_list, &error_status);
	free_env(env_list);
	return (error_status);
}
