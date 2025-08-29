/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:49:34 by lucas             #+#    #+#             */
/*   Updated: 2025/08/29 19:53:50 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	print_env_list(t_env *env)
{
	while (env)
	{
		if (!env->hide && env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	built_env(char **args, t_env **_env)
{
	int	argc;

	if (!_env || !*_env)
	{
		ft_putendl_fd("env: environment not initialized", 2);
		return (1);
	}
	argc = args_count(args);
	if (argc > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	return (print_env_list(*_env));
}
