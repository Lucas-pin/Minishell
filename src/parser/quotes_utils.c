/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:49:26 by manualva          #+#    #+#             */
/*   Updated: 2025/09/11 18:43:39 by manualva         ###   ########.fr       */
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

char	*str_join_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*collect_word(const char *input, int *i, char *quote_type)
{
	char	*result;
	char	*part;
	char	quote;

	result = ft_strdup("");
	*quote_type = 0;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			part = collect_quoted(input, i);
			if (!part)
				return (free(result), NULL);
			if (*quote_type == 0)
				*quote_type = quote;
		}
		else
			part = collect_unquoted(input, i);
		result = str_join_free(result, part);
	}
	return (result);
}
