/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:59:55 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/04 15:09:53 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
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

/* ====== DISPATCH ====== */
int		is_builtin(char *name);
int		is_single_builtin(t_cmd *cmd);
int		run_builtin(t_cmd *cmd, t_env **env, int last_status);
int		run_builtin_parent(t_cmd *cmd, t_env **env, int last_status);

/* ====== BUILTINS ====== */
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_cd(t_cmd *cmd, t_env **env);
int		builtin_export(t_cmd *cmd, t_env **env);
int		builtin_unset(t_cmd *cmd, t_env **env);
int		builtin_exit(t_cmd *cmd, t_env **env, int last_status);

/* ====== EXPORT PRINT ====== */
void	export_print(t_env *env);

/* ====== ENV OPS ====== */
int		valid_key(char *key);
t_env	*env_find(t_env *env, char *name);
int		env_set(t_env **env, char *name, char *value);
int		env_unset(t_env **env, char *name);

#endif
