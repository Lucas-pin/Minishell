/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:08:14 by manualva          #+#    #+#             */
/*   Updated: 2025/09/01 18:13:03 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

static int	write_line(int fd, const char *s)
{
	size_t	len;
	ssize_t	w;

	len = strlen(s);
	while (len > 0)
	{
		w = write(fd, s, len);
		if (w < 0)
			return (-1);
		s += w;
		len -= w;
	}
	if (write(fd, "\n", 1) != 1)
		return (-1);
	return (0);
}

static int	heredoc_read_line(int wfd, const char *delim, const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		if (errno == EINTR)
			exit(130);
		return (1);
	}
	if (ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (2);
	}
	if (write_line(wfd, line) == -1)
	{
		perror("write");
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

static int	heredoc_loop(int wfd, const char *delim)
{
	const char	*prompt;
	int			rc;

	if (isatty(STDIN_FILENO))
		prompt = "> ";
	else
		prompt = "";

	while (1)
	{
		rc = heredoc_read_line(wfd, delim, prompt);
		if (rc != 0)
		{
			if (rc == 1 || rc == 2)
				return (0);
			else
				return (-1);
		}
	}
}

static void	heredoc_writer_child(int wfd, const char *delim)
{
	setup_signals_default();
	if (heredoc_loop(wfd, delim) == -1)
		exit(1);
	exit(0);
}

int	spawn_heredoc_writer(int wfd, const char *delim)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		heredoc_writer_child(wfd, delim);
	setup_signals_parent_wait();
	close(wfd);
	if (waitpid(pid, &st, 0) == -1)
		return (-1);
	setup_signals_shell();
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
	{
		set_exit_status(130);
		return (-2);
	}
	if (WIFEXITED(st) && WEXITSTATUS(st) == 0)
		return (0);
	return (-1);
}
