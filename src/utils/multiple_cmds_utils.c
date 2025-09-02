/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutiple_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:58:53 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 10:55:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	init_cmd_data(t_cmd *cmds, t_cmd_data *data)
{
	data->cmd_qty = count_cmd(cmds);
	data->remaining_cmd = data->cmd_qty;
	data->prev_pipe = -1;
	data->last_pid = -1;
}

int	apply_file_redirs(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	return (0);
}