/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:43:39 by manualva          #+#    #+#             */
/*   Updated: 2025/07/28 18:05:18 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* Processes operators like pipes, redirection, and heredoc tokens in the input
string. */
static int	handle_operator_token(const char *input, int i, t_token **tokens)
{
	if (input[i] == '|' && ++i)
		add_token(tokens, new_token(ft_strdup("|"), T_PIPE));
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		add_token(tokens, new_token(ft_strdup("<<"), T_HEREDOC));
		i += 2;
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		add_token(tokens, new_token(ft_strdup(">>"), T_REDIR_APPEND));
		i += 2;
	}
	else if (input[i] == '<' && ++i)
		add_token(tokens, new_token(ft_strdup("<"), T_REDIR_IN));
	else if (input[i] == '>' && ++i)
		add_token(tokens, new_token(ft_strdup(">"), T_REDIR_OUT));
	return (i);
}

static int	handle_word_token(const char *input, int *i, t_token **tokens)
{
	char		*word;
	t_token		*tok;
	char		quote_type;

	word = collect_word(input, i, &quote_type);
	if (!word)
		return (0);
	tok = new_token(word, T_WORD);
	tok->quote_type = quote_type;
	add_token(tokens, tok);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_operator(input[i]))
			i = handle_operator_token(input, i, &tokens);
		else
		{
			if (!handle_word_token(input, &i, &tokens))
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
	}
	return (tokens);
}
