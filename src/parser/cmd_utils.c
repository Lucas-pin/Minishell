/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:26 by manualva          #+#    #+#             */
/*   Updated: 2025/07/29 10:10:08 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->next = NULL;
	cmd->cmd = NULL;
	return (cmd);
}

void	append_cmd(t_cmd **head, t_cmd *new_tok)
{
	t_cmd	*cur;

	if (!*head)
		*head = new_tok;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_tok;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;

		if (cmds->fd_in != -1)
			close(cmds->fd_in);
		if (cmds->fd_out != -1)
			close(cmds->fd_out);
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
				free(cmds->argv[i++]);
			free(cmds->argv);
		}
		if (cmds->cmd)
			free(cmds->cmd);

		free(cmds);
		cmds = tmp;
	}
}
