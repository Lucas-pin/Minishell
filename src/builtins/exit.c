/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:02:48 by lpin              #+#    #+#             */
/*   Updated: 2025/08/01 19:46:19 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int built_exit(char **argv, t_env **_env)
{
	int status = 0;
	char *aux;

	(void)_env;
	printf("exit\n"); // Bash imprime "exit" al salir
	if (!argv || !*argv)
	{
		exit(1);
		return (1);
	}
	else if (ft_strcmp(*argv, "exit") == 0)
		argv++;
	aux = *argv;
	if (aux)
	{
		if (ft_strncmp(aux, "-", 1) == 0)
			aux++;
		while(*aux)
		{
			if (ft_isdigit(*aux))
			{
				aux++;
				continue;
			}
			else
			{
				ft_putendl_fd("bash: exit: numeric argument required", 2);
				exit(2);
			}
		}
		status = ft_atoi(*argv);
	}
	exit(status);
	return (status);
}