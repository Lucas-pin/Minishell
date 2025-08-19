/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:23:23 by lpin              #+#    #+#             */
/*   Updated: 2025/08/10 23:52:43 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	redirect_pipes(int *current_pipe, int prev_pipe,
		int remaining_cmd, int cmd_qty)
{
	if (remaining_cmd == cmd_qty && remaining_cmd > 1)
	{
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
	}
	else if (remaining_cmd == 1)
	{
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
	}
	else
	{
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
	}
}

void	pipe_closer(int *current_pipe, int remaining_cmd, int cmd_qty)
{
	if (remaining_cmd == cmd_qty && remaining_cmd > 1)
		close(current_pipe[0]);
	else if (remaining_cmd != 1)
		close(current_pipe[0]);
}

void	ft_wait(int remaining_cmd)
{
	while (remaining_cmd > 0)
	{
		wait(NULL);
		remaining_cmd--;
	}
}

int	*pipe_creator(int *pipes, int remaining_cmd, int cmq_qty)
{
	(void)cmq_qty;
	if (remaining_cmd > 1)
	{
		if (pipe(pipes) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}