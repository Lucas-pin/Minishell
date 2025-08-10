/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:26 by manualva          #+#    #+#             */
/*   Updated: 2025/08/11 00:59:49 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins_utils.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*aux;
	int		cmd_qty;

	aux = cmd;
	cmd_qty = 0;
	if (!cmd)
		return (0);
	while (aux)
	{
		cmd_qty++;
		aux = aux->next;
	}
	return (cmd_qty);
}

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
	cmd->cmd_path = NULL;
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
	int		is_ext;

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
		is_ext = (cmds->cmd && is_builtin(cmds->cmd) == -1);
		if (cmds->cmd)
			free(cmds->cmd);
		if (cmds->cmd_path && is_ext)
			free(cmds->cmd_path);
		free(cmds);
		cmds = tmp;
	}
}
