/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:30:59 by manualva          #+#    #+#             */
/*   Updated: 2025/09/02 18:04:36 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

int	run_heredoc(const char *delimiter)
{
	int	pipe_fds[2];
	int	rc;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	rc = spawn_heredoc_writer(pipe_fds[1], delimiter);
	if (rc != 0)
	{
		close(pipe_fds[0]);
		if (rc == -1)
			perror("heredoc");
		return (-1);
	}
	return (pipe_fds[0]);
}
