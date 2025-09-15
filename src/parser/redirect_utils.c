/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:33:42 by manualva          #+#    #+#             */
/*   Updated: 2025/09/15 19:02:02 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

static void	printf_redirection_error(const char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	if (filename && *filename)
		ft_putstr_fd((char *)filename, 2);
	else
		ft_putstr_fd("(null)", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)strerror(errno), 2);
	set_exit_status(1);
}

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
		set_exit_status(-2);
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
		if (file_token && file_token->str)
			printf_redirection_error(file_token->str);
		else
			printf_redirection_error("(null)");
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
