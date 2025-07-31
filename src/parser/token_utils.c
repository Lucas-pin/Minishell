/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:27 by manualva          #+#    #+#             */
/*   Updated: 2025/07/28 18:05:39 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *str, int type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = str;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **head, t_token *new_tok)
{
	t_token	*cur;

	if (!*head)
		*head = new_tok;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_tok;
	}
}

char	**token_list_to_argv(t_token *start, t_token *end)
{
	t_token	*cur;
	int		count;
	char	**argv;
	int		debug_index;

	cur = start;
	count = 0;
	while (cur && cur != end)
	{
		if (cur->type == T_WORD)
			count++;
		cur = cur->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	cur = start;
	debug_index = 0;
	while (cur && cur != end)
	{
		if (cur->type == T_WORD)
		{
			argv[debug_index] = ft_strdup(cur->str);
			debug_index++;
		}
		cur = cur->next;
	}
	argv[debug_index] = NULL;
	return (argv);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token->next;
		if (token->str != NULL)
			free(token->str);
		free(token);
		token = tmp;
	}
}
