/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:50:58 by manualva          #+#    #+#             */
/*   Updated: 2025/07/14 11:20:23 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* Processes tokens until a pipe is encountered, then creates a new command from
the tokens. */
static void	parse_till_pipe(t_token **cur, t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return ;
	handle_redirection(start, cmd);
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

	cmd = init_cmd();
	if (!cmd)
		return (0);
	handle_redirection(start, cmd);
	cmd->argv = token_list_to_argv(*start, NULL);
	append_cmd(cmds, cmd);
	return (1);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_token	*cur;
	t_token	*start;

	cmds = NULL;
	cur = tokens;
	start = cur;
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
			free_tokens(start);
			return (cmds);
		}
	}
	free_tokens(start);
	return (cmds);
}
