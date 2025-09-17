/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:52:07 by manualva          #+#    #+#             */
/*   Updated: 2025/09/17 20:20:48 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

int	print_error(char *token_str, int error_type)
{
	if (!token_str)
		token_str = "newline";

	if (error_type == 1)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			token_str);
		set_exit_status(2);
	}
	return (1);
}
