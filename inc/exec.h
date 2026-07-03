/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 05:47:59 by adchebbi          #+#    #+#             */
/*   Updated: 2026/07/03 21:05:42 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "env.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>

/* ====== EXEC ===== */
int		exec_cmds(t_cmd *cmds, t_env **env, int last_status);
void	exec_child(t_cmd *cmd, t_env *env);
char	*resolve_path(char *cmd, t_env *env);
char	*env_get_value(t_env *env, char *name);
int		apply_redirs(t_redir *r);
char	**env_to_array(t_env *env);

/* ====== HERE_DOC ===== */
int		handle_heredoc(char *delimiter, t_env *env, int quoted);
int		run_heredocs_pre_exec(t_cmd *cmds, t_env *env);
int		is_delimiter(char *line, char *delimiter);

#endif
