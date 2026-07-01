/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:07:27 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 13:46:47 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"
# include "expander.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* ====== PARSER ====== */
t_cmd	*parse(t_token *toks, int *err_status);
int		push_arg(t_cmd *c, char *value);
int		handle_redir(t_token **tok, t_cmd *cur);
void	cmds_free(t_cmd *cmds);
void	err_msg(const char *prefix, const char *msg);

/* ===== UTILS ===== */
char	**ms_split(char const *s);
int		check_unclosed_quotes(char *line);
char	*add_spaces_ops(char *line);
int		check_tokens_syntax(t_token *tokens);

#endif