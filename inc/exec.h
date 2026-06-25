/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 05:47:59 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/25 17:51:40 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "env.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

/* ====== EXEC ===== */
int		exec_cmds(t_cmd *cmds, t_env *env);
void	exec_child(t_cmd *cmd, t_env *env);
char	*resolve_path(char *cmd, t_env *env);
char	*env_get_value(t_env *env, char *name);
int		apply_redirs(t_redir *r);
char	**env_to_array(t_env *env);

/* ====== HERE_DOC ===== */
int		handle_heredoc(char *delimiter);
int		pre_open_heredocs(t_cmd *cmds);

#endif
