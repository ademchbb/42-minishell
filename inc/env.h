/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:24:46 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 06:44:23 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include "exec.h"
# include "builtins.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* ====== ENV ====== */
t_env	*new_env_node(char *name, char *value);
void	add_back_env(t_env **env, t_env *new);
t_env	*init_env(char **envp);

/* ==== UTILS ==== */
void	free_env(t_env *env);

#endif