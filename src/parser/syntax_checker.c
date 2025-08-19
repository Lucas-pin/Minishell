/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:36:02 by manualva          #+#    #+#             */
/*   Updated: 2025/07/28 18:05:35 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_syntax(t_token *tokens)
{
	t_token	*prev = NULL;

	while (tokens)
	{
		if (tokens->type == T_PIPE && check_pipe(tokens, prev))
			return (1);
		if ((tokens->type == T_REDIR_IN || tokens->type == T_REDIR_OUT
			|| tokens->type == T_APPEND || tokens->type == T_HEREDOC)
			&& check_redirection(tokens))
			return (1);
		if (tokens->type == T_WORD && check_word(tokens))
			return (1);
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
