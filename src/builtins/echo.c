/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:47:09 by lpin              #+#    #+#             */
/*   Updated: 2025/08/28 22:24:56 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	print_words(char **args)
{
	int	index;

	index = 0;
	while (args && args[index])
	{
		if (index > 0)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(args[index], 1);
		index++;
	}
}

static int	handle_option(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	if (ft_strcmp(arg, "-n") == 0)
		return (1);
	ft_putstr_fd("echo: invalid option -- ", 2);
	ft_putendl_fd(arg, 2);
	return (-1);
}

int	built_echo(char **args, t_env **_env)
{
	int	has_n;

	(void)_env;
	if (!args || !*args)
		return (1);
	has_n = handle_option(args[1]);
	if (has_n < 0)
		return (2);
	if (has_n == 1)
		print_words(&args[2]);
	else
	{
		print_words(&args[1]);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
