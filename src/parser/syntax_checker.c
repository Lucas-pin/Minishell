/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:36:02 by manualva          #+#    #+#             */
/*   Updated: 2025/09/17 20:19:46 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

static int	check_pipe_syntax(t_token *tokens, t_token *prev)
{
	if (tokens->type == T_PIPE && check_pipe(tokens, prev))
		return (1);
	return (0);
}

static int	check_redir_syntax(t_token *tokens)
{
	if ((tokens->type == T_REDIR_IN || tokens->type == T_REDIR_OUT
			|| tokens->type == T_REDIR_APPEND || tokens->type == T_HEREDOC)
		&& check_redirection(tokens))
		return (1);
	return (0);
}

static int	check_word_syntax(t_token *tokens)
{
	if (tokens->type == T_WORD && check_word(tokens))
		return (1);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (check_pipe_syntax(tokens, prev)
			|| check_redir_syntax(tokens)
			|| check_word_syntax(tokens))
		{
			set_exit_status(2);
			return (1);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
