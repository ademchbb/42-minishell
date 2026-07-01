/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:07 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 07:08:02 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "signals.h"

int	g_status = 0;

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
	init_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (g_status == 130)
        {
            error_status = g_status;
            g_status = 0;
        }
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (check_unclosed_quotes(line))
		{
			error_status = 2;
			free(line);
			continue ;
		}
		line = add_spaces_ops(line);
		if (!line)
			continue ;
		split_res = ms_split(line);
		free(line);
		if (!split_res)
			continue ;
		tokens = lexer(split_res);
		free(split_res);
		if (!tokens)
			continue ;
		if (check_tokens_syntax(tokens))
		{
			error_status = 2;
			clear_token(&tokens);
			continue ;
		}
		expander(tokens, env_list, error_status);
		quote_removal(tokens);
		cmds = parse(tokens, &error_status);
        clear_token(&tokens);
        if (!cmds)
            continue ;
        error_status = exec_cmds(cmds, &env_list, error_status);
        cmds_free(cmds);
		if (g_status == 130)
        {
            error_status = g_status;
            g_status = 0;
        }
    }
    free_env(env_list);
    return (error_status);
}
