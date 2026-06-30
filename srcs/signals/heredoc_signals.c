/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:21 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/30 16:55:24 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/*écrit "\b\b  \b\b" (Backspace) pour effacer ces 2 caractères de l'écran
et replace le curseur exactement là où il était*/
static void	handle_heredoc_sigquit(int signal)
{
	(void)signal;
	write(1, "\b\b  \b\b", 6);
}

void	init_signals_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = SIG_DFL;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &handle_heredoc_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
