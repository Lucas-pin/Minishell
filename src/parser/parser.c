/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:50:58 by manualva          #+#    #+#             */
/*   Updated: 2025/09/15 19:18:11 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;

	cmds = NULL;
	parse_tokens(&tokens, &cmds);
	return (cmds);
}
