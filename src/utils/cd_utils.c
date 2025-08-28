/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:54:26 by lpin              #+#    #+#             */
/*   Updated: 2025/08/28 21:12:47 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_utils.h"
#include "../../include/minishell.h"
#include "../../include/structs.h"

char *home_exists(t_env **_env)
{
	t_env	*home_env;

	if (!_env || !*_env)
		return (NULL);
	home_env = find_key(_env, "HOME=");
	if (home_env && home_env->value)
		return (home_env->value);
	return (NULL);
}

int check_cd_error(int argc, char **args, t_env **_env)
{
	t_env	*oldpwd_env;

	oldpwd_env = NULL;
	if (argc < 1)
		return (1);
	if (argc > 2)
		return (cd_logical_error("too many arguments"));
	if (argc == 2 && ft_strcmp(args[1], "-") == 0)
	{
		oldpwd_env = find_key(_env, "OLDPWD=");
		if (!oldpwd_env || oldpwd_env->value == NULL)
			return (cd_logical_error("OLDPWD not set"));
	}
	if ((argc == 1 || (argc > 1 && ft_strncmp(args[1], "~", 1) == 0))
		&& home_exists(_env) == NULL)
		return (cd_logical_error("HOME not set"));
	return (0);
}

int cd_logical_error(const char *msg)
{
	if (msg)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd((char *)msg, 2);
	}
	return (1);
}

int cd_syscall_error(const char *path, int saved)
{
	ft_putstr_fd("cd: ", 2);
	if (path)
	{
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)strerror(saved), 2);
	return (1);
}