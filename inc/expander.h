/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:22:30 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 12:51:06 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ====== EXPANDER ====== */
void	expander(t_token **tokens, t_env *env, int error_status);

/* ====== EXPANDER UTILS ====== */
char	*get_env_val(t_env *env, char *name);
int		get_name_len(char *str, int start);
char	*assemble_str(char *before, char *variable_value, char *after);
char	*replace_variable(char *old_str, int dollar,
			t_env *env, int error_status);
char	*expand_heredoc_line(char *line, t_env *env, int error_status);

#endif