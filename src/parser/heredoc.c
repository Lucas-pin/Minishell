/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:30:59 by manualva          #+#    #+#             */
/*   Updated: 2025/07/29 09:52:47 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	write_heredoc_content(int write_fd, const char *delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	read_len;

	line = NULL;
	len = 0;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		read_len = getline(&line, &len, stdin);
		if (read_len == -1)
		{
			free(line);
			return (-1);
		}
		if (line[read_len - 1] == '\n')
			line[read_len - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
	}
	free(line);
	return (0);
}

int	run_heredoc(const char *delimiter)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (write_heredoc_content(pipe_fds[1], delimiter) == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}
