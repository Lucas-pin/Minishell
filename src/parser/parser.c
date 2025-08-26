/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:50:58 by manualva          #+#    #+#             */
/*   Updated: 2025/08/26 16:09:56 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Processes tokens until a pipe is encountered, then creates a new command
from the tokens. */
static void	parse_till_pipe(t_token **cur, t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;
	int		redir_status;

	cmd = init_cmd();
	if (!cmd)
		return ;
	redir_status = handle_redirection(start, cmd);
	if (redir_status == -1)
	{
		free(cmd);
		*cur = NULL;
		return ;
	}
	if (redir_status == -2)
	{
		free(cmd);
		*start = NULL;
		*cur = NULL;
		return ;
	}
	cmd->argv = token_list_to_argv(*start, *cur);
	append_cmd(cmds, cmd);
	if (*cur)
	{
		*cur = (*cur)->next;
		*start = *cur;
	}
}

static int	handle_last_command(t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;
	int	 redir_status;

	cmd = init_cmd();
	if (!cmd)
		return (0);
	redir_status = handle_redirection(start, cmd);
	if (redir_status == -1)
	{
		free(cmd);
		return (0);
	}
	if (redir_status == -2)
	{
		free(cmd);
		return (0);
	}
	cmd->argv = token_list_to_argv(*start, NULL);
	append_cmd(cmds, cmd);
	return (1);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_token	*cur;
	t_token	*start;
    t_token	*head;

	cmds = NULL;
	cur = tokens;
	start = cur;
    head = tokens;
	while (cur)
	{
		if (cur->type == T_PIPE)
		{
			parse_till_pipe(&cur, &start, &cmds);
		}
		else
			cur = cur->next;
	}
	if (start)
	{
		if (!handle_last_command(&start, &cmds))
		{
	    free_tokens(head);
			return (cmds);
		}
	}
    free_tokens(head);
	return (cmds);
}
