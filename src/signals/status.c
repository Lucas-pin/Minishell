/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:12:20 by manualva          #+#    #+#             */
/*   Updated: 2025/09/03 18:54:34 by lpin             ###   ########.fr       */
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
