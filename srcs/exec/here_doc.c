/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 17:40:14 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/25 18:18:53 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

extern int	g_status;

static void	read_heredoc(int write_fd, char *delimiter)
{
	char	*line;

	init_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n",
				2);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

static int	check_heredoc_status(pid_t pid, int *fds)
{
	int	status;

	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
		close(fds[0]);
		return (-3);
	}
	return (fds[0]);
}

int	handle_heredoc(char *delimiter)
{
	int		fds[2];
	pid_t	pid;
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	if (pipe(fds) == -1)
		return (close(save_stdin), -1);
	init_signals_parent();
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (close(save_stdin), -1);
	}
	if (pid == 0)
	{
		close(fds[0]);
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
		read_heredoc(fds[1], delimiter);
	}
	close(save_stdin);
	close(fds[1]);
	return (check_heredoc_status(pid, fds));
}

// int	pre_open_heredocs(t_cmd *cmds)
// {
// 	t_cmd		*curr;
// 	t_redir		*r;
// 	int			fd;

// 	curr = cmds;
// 	while (curr)
// 	{
// 		r = curr->redirs;
// 		while (r)
// 		{
// 			if (r->type == R_HEREDOC)
// 			{
// 				fd = handle_heredoc(r->target);
// 				if (fd == -3)
// 					return (-3);
// 				free(r->target);
// 				r->target = ft_itoa(fd);
// 			}
// 			r = r->next;
// 		}
// 		curr = curr->next;
// 	}
// 	return (0);
// }
