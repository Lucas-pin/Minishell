/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:12:20 by manualva          #+#    #+#             */
/*   Updated: 2025/07/11 11:12:05 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

static int	g_status = 0;

void	set_exit_status(int status)
{
	g_status = status;
}

int	get_exit_status(void)
{
	return (g_status);
}
