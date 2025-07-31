/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:52:07 by manualva          #+#    #+#             */
/*   Updated: 2025/07/28 18:06:00 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_error_type(int i)
{
	if (i == 1)
		ft_printf("Syntax Error: ");
}

int	print_error(char *str, int error)
{
	if (error)
	{
		print_error_type(error);
		ft_printf("%s", str);
	}
	return (1);
}
