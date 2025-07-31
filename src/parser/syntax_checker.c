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
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (!prev || prev->type == T_PIPE)
			{
				return (print_error("Unexpected token '|'\n", 1));
			}
			if (!tokens->next)
			{
				return (print_error("Unexpected end after '|'\n", 1));
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}

int	contains_forbidden_chars(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (strchr(FORBIDDEN_CHARS, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_special_syntax(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_WORD && tokens->quote_type == 0)
		{
			if (contains_forbidden_chars(tokens->str))
			{
				ft_printf("Syntax Error: Forbidden character in token '%s'\n",
					tokens->str);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
