/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:13:36 by manualva          #+#    #+#             */
/*   Updated: 2025/09/05 17:24:05 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*free_token_range(t_token *start, t_token *end)
{
	t_token	*tmp;
	t_token	*next;

	if (!start)
		return (NULL);
	tmp = start;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		if (end == NULL)
			tmp = next;
		else
		{
			if (tmp == end)
				break ;
			tmp = next;
		}
	}
	return (next);
}
