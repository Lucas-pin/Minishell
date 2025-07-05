/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:47:09 by lpin              #+#    #+#             */
/*   Updated: 2025/07/05 20:00:35 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	print_without_newline(char **argv)
{
	char *temp;

	if (*argv == "" || !*argv)
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

	if (*argv == "" || !*argv)
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

void built_echo(char **argv)
{

	if (!argv)
		return ;
	argv++;
	if (ft_strcmp(*argv, "-n") == 0)
	{
		argv++;
		print_without_newline(argv);
	}
	else
		print_with_newline(argv);
}