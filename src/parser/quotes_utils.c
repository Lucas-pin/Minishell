/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:49:26 by manualva          #+#    #+#             */
/*   Updated: 2025/08/28 19:15:35 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*collect_quoted(const char *input, int *i)
{
	int		start;
	char	*part;
	char	quote;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		ft_printf("Syntax error: Unclosed quote [%c]\n", quote);
		return (NULL);
	}
	part = substr_dup(input, start, *i - start);
	(*i)++;
	return (part);
}

static char	*collect_unquoted(const char *input, int *i)
{
	int		start;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	return (substr_dup(input, start, *i - start));
}

char	*collect_word(const char *input, int *i, char *quote_type)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		*quote_type = input[*i];
		return (collect_quoted(input, i));
	}
	return (collect_unquoted(input, i));
}
