/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:47:09 by lpin              #+#    #+#             */
/*   Updated: 2025/08/05 17:15:20 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	print_without_newline(char **argv)
{
	char *temp;

	if (ft_strcmp(*argv, "") == 0 || !*argv)
		return ;
	temp = NULL;
	temp = ft_strdup(*argv);
	argv++;
	while (*argv)
	{
		temp = ft_strjoin_free_s1(temp, " ");
		temp = ft_strjoin_free_s1(temp, *argv);
		argv++;
	}
	ft_putstr_fd(temp, 1);
	if (temp)
		free(temp);
}

static void	print_with_newline(char **argv)
{
	char *temp;

	if (ft_strcmp(*argv, "") == 0 || !*argv)
	{
		printf("\n");
		return ;
	}
	temp = NULL;
	temp = ft_strdup(*argv);
	argv++;
	while (*argv)
	{
		temp = ft_strjoin_free_s1(temp, " ");
		temp = ft_strjoin_free_s1(temp, *argv);
		argv++;
	}
	ft_putendl_fd(temp, 1);
	if (temp)
		free(temp);
}

int built_echo(char **argv, t_env **_env)
{

	(void)_env;
	if (!argv)
		return (1);
	argv++;
	if (ft_strcmp(*argv, "-n") == 0)
	{
		argv++;
		print_without_newline(argv);
	}
	else
		print_with_newline(argv);
	return (0);
}
