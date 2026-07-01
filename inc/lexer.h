/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:48:29 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 13:45:54 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	READ_IN,
	READ_OUT
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	int				quoted;
	struct s_token	*next;
}	t_token;

/* ====== LEXER ====== */
t_token		*new_token(char *word, t_token_type type);
void		add_back_token(t_token **token, t_token *new);
t_token		*define_token_type(char *str);
t_token		*lexer(char **split_res);
void		clear_token(t_token **lst);

/* ====== QUOTE REMOVAL ====== */
void		quote_removal(t_token *tokens);

#endif
