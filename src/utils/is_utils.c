/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:07 by manualva          #+#    #+#             */
/*   Updated: 2025/08/24 20:18:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

int is_null_or_empty(char *str)
{
	if (!str || ft_strlen(str) == 0)
		return (1);
	return (0);
}

/*
** Validate shell identifier names used by export/unset.
** Rules: first char must be alpha or '_'; rest up to '=' (or given len)
** must be alnum or '_'.
*/
int	is_valid_identifier(const char *s)
{
	int i;

	if (!s || s[0] == '\0' || s[0] == '=')
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier_n(const char *s, int len)
{
	int i;

	if (!s || len <= 0)
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
