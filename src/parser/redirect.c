/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:12:14 by manualva          #+#    #+#             */
/*   Updated: 2025/09/17 20:18:20 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_single_redirection(t_token **tokens, t_token **cur,
	t_token **prev, t_cmd *cmd)
{
	int	redir_result;

	if (!(*cur)->next)
	{
		print_error("newline", 1);
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

int	handle_redirection(t_token **tokens, t_cmd *cmd)
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
