/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:49:34 by lucas             #+#    #+#             */
/*   Updated: 2025/08/24 19:46:40 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int handle_args(char **args)
{
	if (!args || !args[1])
		return (0);
	if (args[1][0] == '-')
	{
		ft_putstr_fd("env: invalid option -- ", 2);
		ft_putendl_fd(args[1], 2);
		return (2);
	}
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

static int print_env_list(t_env *env)
{
	while (env)
	{
		if (!env->hide && env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int built_env(char **args, t_env **_env)
{
	int return_code;

	if (!_env || !*_env)
	{
		ft_putendl_fd("env: environment not initialized", 2);
		return (1);
	}
	if (args_count(args) > 1)
	{
		return_code = handle_args(args);
		if (return_code != 0)
			return (return_code);
	}
	return (print_env_list(*_env));
}
