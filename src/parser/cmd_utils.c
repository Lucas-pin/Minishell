/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:07:26 by manualva          #+#    #+#             */
/*   Updated: 2025/09/09 18:03:58 by manualva         ###   ########.fr       */
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

void	free_single_cmd(t_cmd *cmd)
{
	int	i;
	int	is_ext;

	if (!cmd)
		return ;
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	is_ext = (cmd->cmd && is_builtin(cmd->cmd) == -1);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_path && is_ext)
		free(cmd->cmd_path);
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_single_cmd(cmds);
		cmds = tmp;
	}
}
