/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:07 by manualva          #+#    #+#             */
/*   Updated: 2025/08/19 21:47:23 by lpin             ###   ########.fr       */
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
