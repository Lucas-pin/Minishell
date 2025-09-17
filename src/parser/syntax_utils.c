/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:27:06 by manualva          #+#    #+#             */
/*   Updated: 2025/09/17 20:19:18 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

static int	contains_forbidden_chars(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(FORBIDDEN_CHARS, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe(t_token *tok, t_token *prev)
{
	if (!prev || prev->type == T_PIPE)
		return (print_error("|", 1));
	if (!tok->next)
		return (print_error("newline", 1));
	return (0);
}

int	check_redirection(t_token *tok)
{
	if (!tok->next || tok->next->type != T_WORD)
		return (print_error("newline", 1));
	if (tok->type == T_HEREDOC && tok->next->str[0] == '\0')
		return (print_error("newline", 1));
	return (0);
}

int	check_word(t_token *tok)
{
	if (tok->quote_type == -1)
		return (print_error("newline", 1));
	if (tok->quote_type == 0 && contains_forbidden_chars(tok->str))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			tok->str);
		set_exit_status(2);
		return (1);
	}
	return (0);
}
