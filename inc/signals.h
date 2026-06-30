/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:14:39 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/30 16:16:10 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define _XOPEN_SOURCE 700
# include "exec.h"
# include "expander.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "signal.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>

extern int	g_status;

void		init_signals(void);
void		init_signals_child(void);
void		init_signals_parent(void);
void		init_signals_heredoc(void);

#endif