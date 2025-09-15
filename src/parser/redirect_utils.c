/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:42 by manualva          #+#    #+#             */
/*   Updated: 2025/09/15 17:58:42 by lpin             ###   ########.fr       */
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

static int	get_redirection_fd(t_token *cur)
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
	}
	return (fd);
}

int	process_redirection(t_token *cur, t_cmd *cmd)
{
	int	fd;

	fd = get_redirection_fd(cur);
	if (fd < 0)
		return (fd);
	if (cur->type == T_REDIR_IN || cur->type == T_HEREDOC)
		cmd->fd_in = fd;
	else
		cmd->fd_out = fd;
	return (0);
}

void	remove_redirection_tokens(t_token **tokens, t_token *prev,
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
