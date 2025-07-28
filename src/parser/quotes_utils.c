/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:49:26 by manualva          #+#    #+#             */
/*   Updated: 2025/07/14 11:21:56 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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

// Handles appending a part to the current word
static char	*append_part(char *word, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(word, part);
	free(word);
	free(part);
	return (tmp);
}

// Handles the next chunk of the word (quoted or unquoted)
static char	*get_next_part(const char *input, int *i, char *quote_type)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		*quote_type = input[*i];
		return (collect_quoted(input, i));
	}
	return (collect_unquoted(input, i));
}

char	*collect_word(const char *input, int *i, char *quote_type)
{
	char	*word;
	char	*part;

	word = ft_strdup("");
	*quote_type = 0;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		part = get_next_part(input, i, quote_type);
		if (!part)
		{
			free(word);
			return (NULL);
		}
		word = append_part(word, part);
	}
	return (word);
}
