/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:07 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/17 23:19:54 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void init_shell(int *error_status)
{
	*error_status = 0;
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	**split_res;
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*env_list;
	int		error_status;

	(void)ac; // éviter les erreurs de flags inutilisés
	(void)av;
	init_shell(&error_status);
	env_list = init_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		split_res = ms_split(line);
		free(line);
		if (!split_res)
			continue ;
		tokens = lexer(split_res);
		free(split_res);
		if (!tokens)
			continue ;
		expander(tokens, env_list, error_status);
		quote_removal(tokens);
		cmds = parse(tokens, &error_status);
		clear_token(&tokens);
		if (!cmds)
			continue ;
		error_status = exec_cmds(cmds, env_list);
		cmds_free(cmds);
	}
	free_env(env_list);
	return (error_status);
}
