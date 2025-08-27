/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:50:58 by manualva          #+#    #+#             */
/*   Updated: 2025/08/27 20:44:39 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*init_and_handle_redir(t_token **start, t_token **cur)
{
	t_cmd	*cmd;
	int		redir_status;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	redir_status = handle_redirection(start, cmd);
	if (redir_status == -1)
	{
		free(cmd);
		*cur = NULL;
		return (NULL);
	}
	if (redir_status == -2)
	{
		free(cmd);
		*start = NULL;
		*cur = NULL;
		return (NULL);
	}
	return (cmd);
}

static void	parse_till_pipe(t_token **cur, t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;
	int		redir_status;

	cmd = init_and_handle_redir(start, cur);
	if (!cmd)
		return ;
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
	int		redir_status;

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

static void	parse_tokens(t_token *tokens, t_cmd **cmds)
{
	t_token	*cur;
	t_token	*start;
    t_token	*head;

	cur = tokens;
	start = cur;
    head = tokens;
	while (cur)
	{
		if (cur->type == T_PIPE)
			parse_till_pipe(&cur, &start, cmds);
		else
			cur = cur->next;
	}
	if (start)
		handle_last_command(&start, cmds);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_token	*head;

	cmds = NULL;
	head = tokens;
	parse_tokens(tokens, &cmds);
	free_tokens(head);
	return (cmds);
}
