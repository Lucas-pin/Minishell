/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:12:14 by manualva          #+#    #+#             */
/*   Updated: 2025/07/29 09:42:39 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_file_for_redirection(t_token *file_token, t_token *redir_token)
{
	int	fd;

	if (redir_token->type == T_REDIR_IN)
		fd = open(file_token->str, O_RDONLY);
	else if (redir_token->type == T_REDIR_OUT)
		fd = open(file_token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static int	process_redirection(t_token *cur, t_cmd *cmd)
{
	t_token	*file_token;
	int		fd;

	file_token = cur->next;
	if (!file_token || !file_token->str)
	{
		print_error("Near unexpected token 'newline'\n", 1);
		return (-1);
	}
	if (cur->type == T_HEREDOC)
		fd = run_heredoc(file_token->str);
	else
		fd = open_file_for_redirection(file_token, cur);

	if (fd == -1)
	{
		if (cur->type == T_HEREDOC && errno == EINTR)
			return (-2);
		perror("minishell");
		return (-1);
	}
	if (cur->type == T_REDIR_IN || cur->type == T_HEREDOC)
		cmd->fd_in = fd;
	else
		cmd->fd_out = fd;
	return (0);
}

static void	remove_redirection_tokens(t_token **tokens, t_token *prev,
	t_token *cur)
{
	t_token	*file_token;
	t_token	*next;

	file_token = cur->next;
	if (file_token != NULL)
		next = file_token->next;
	else
		next = NULL;

	if (prev != NULL)
		prev->next = next;
	else
		*tokens = next;
	if (file_token != NULL)
	{
		if (file_token->str != NULL)
			free(file_token->str);
		free(file_token);
	}

	if (cur->str != NULL)
		free(cur->str);
	free(cur);
}

static int	handle_single_redirection(t_token **tokens, t_token **cur,
	t_token **prev, t_cmd *cmd)
{
	int	redir_result;

	if (!(*cur)->next)
	{
		print_error("Near unexpected token 'newline'\n", 1);
		return (-1);
	}
	redir_result = process_redirection(*cur, cmd);
	if (redir_result != 0)
		return (redir_result);
	remove_redirection_tokens(tokens, *prev, *cur);
	if (*prev != NULL)
		*cur = (*prev)->next;
	else
		*cur = *tokens;

	if (!*cur)
		return (1);
	return (0);
}

int		handle_redirection(t_token **tokens, t_cmd *cmd)
{
	t_token	*cur;
	t_token	*prev;
	int		step_result;

	cur = *tokens;
	prev = NULL;
	while (cur != NULL && cur->type != T_PIPE)
	{
		if (cur->type == T_REDIR_IN || cur->type == T_REDIR_OUT
			|| cur->type == T_REDIR_APPEND || cur->type == T_HEREDOC)
		{
			step_result = handle_single_redirection(tokens, &cur, &prev, cmd);
			if (step_result == -1)
				return (-1);
			if (step_result == -2)
				return (-2);
			if (step_result == 1)
				break ;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
