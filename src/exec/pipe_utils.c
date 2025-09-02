/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:23:23 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 11:10:20 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	redirect_pipes(int *current_pipe, t_cmd_data *data)
{
	if (data->remaining_cmd == data->cmd_qty && data->remaining_cmd > 1)
	{
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
	}
	else if (data->remaining_cmd == 1)
	{
		if (data->prev_pipe != -1)
		{
			dup2(data->prev_pipe, STDIN_FILENO);
			close(data->prev_pipe);
		}
	}
	else
	{
		if (data->prev_pipe != -1)
		{
			dup2(data->prev_pipe, STDIN_FILENO);
			close(data->prev_pipe);
		}
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
	}
}

void	pipe_closer(int *current_pipe, t_cmd_data *data)
{
	if (data->remaining_cmd == data->cmd_qty && data->remaining_cmd > 1)
		close(current_pipe[0]);
	else if (data->remaining_cmd != 1)
		close(current_pipe[0]);
}

int	*pipe_creator(int *pipes, t_cmd_data *data)
{
	if (data->remaining_cmd > 1)
	{
		if (pipe(pipes) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}
