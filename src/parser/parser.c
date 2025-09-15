/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:50:58 by manualva          #+#    #+#             */
/*   Updated: 2025/09/15 18:48:59 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*init_and_handle_redir(t_token **start, int *redir_status)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	*redir_status = handle_redirection(start, cmd);
	if (*redir_status == -1)
	{
		free(cmd);
		return (NULL);
	}
	if (*redir_status == -2)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

static void	parse_till_pipe(t_token **cur, t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;
	t_token	*after;
	int		redir_status;

	cmd = init_and_handle_redir(start, &redir_status);
	if (redir_status == -2)
	{
		// Heredoc cancel: free all remaining tokens and stop parsing
		after = free_token_range(*start, NULL);
		(void)after;
		*start = NULL;
		*cur = NULL;
		return ;
	}
	if (redir_status == -1)
	{
		// Redirection open failed: skip this segment but continue with next
		after = free_token_range(*start, *cur);
		*cur = after;
		*start = after;
		return ;
	}
	// Success path
	cmd->argv = token_list_to_argv(*start, *cur);
	append_cmd(cmds, cmd);
	after = free_token_range(*start, *cur);
	*cur = after;
	*start = after;
}

static int	handle_last_command(t_token **start, t_cmd **cmds)
{
	t_cmd	*cmd;
	int		redir_status;
	t_token	*after;

	cmd = init_cmd();
	if (!cmd)
		return (0);
	redir_status = handle_redirection(start, cmd);
	if (redir_status == -2)
	{
		free(cmd);
		after = free_token_range(*start, NULL);
		(void)after;
		*start = NULL;
		return (0);
	}
	if (redir_status == -1)
	{
		// Redirection open failed on last segment: skip generating a command
		free(cmd);
		after = free_token_range(*start, NULL);
		(void)after;
		*start = NULL;
		return (0);
	}
	cmd->argv = token_list_to_argv(*start, NULL);
	append_cmd(cmds, cmd);
	after = free_token_range(*start, NULL);
	(void)after;
	*start = NULL;
	return (1);
}

static void	parse_tokens(t_token **tokens, t_cmd **cmds)
{
	t_token	*cur;
	t_token	*start;

	cur = *tokens;
	start = cur;
	while (cur)
	{
		if (cur->type == T_PIPE)
			parse_till_pipe(&cur, &start, cmds);
		else
			cur = cur->next;
	}
	if (start)
		handle_last_command(&start, cmds);
	*tokens = NULL;
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;

	cmds = NULL;
	parse_tokens(&tokens, &cmds);
	return (cmds);
}
