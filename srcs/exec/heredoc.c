/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 17:40:14 by ragolden          #+#    #+#             */
/*   Updated: 2026/07/01 14:24:51 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

extern int	g_status;

static void	write_heredoc_line(int write_fd, char *line, t_env *env, int quoted)
{
	if (!quoted)
		line = expand_heredoc_line(line, env, g_status);
	write(write_fd, line, ft_strlen(line));
	if (line[ft_strlen(line) - 1] != '\n')
		write(write_fd, "\n", 1);
	free(line);
}

static void	read_heredoc(int write_fd, char *delimiter, t_env *env, int quoted)
{
	char	*line;

	init_signals_heredoc();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("\nminishell: warning: here-document "
				"delimited by end-of-file\n", 2);
			break ;
		}
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_heredoc_line(write_fd, line, env, quoted);
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

int	handle_heredoc(char *delimiter, t_env *env, int quoted)
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
		read_heredoc(fds[1], delimiter, env, quoted);
	}
	close(save_stdin);
	close(fds[1]);
	return (check_heredoc_status(pid, fds));
}
