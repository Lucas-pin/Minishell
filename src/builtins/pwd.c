/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:23:58 by lpin              #+#    #+#             */
/*   Updated: 2025/08/29 19:54:43 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	pwd_syscall_error(int saved)
{
	ft_putstr_fd("pwd: ", 2);
	ft_putendl_fd((char *)strerror(saved), 2);
	return (1);
}

int	built_pwd(char **args, t_env **_env)
{
	char	*cwd;
	int		argc;

	(void)_env;
	if (!args || !*args)
		return (1);
	argc = args_count(args);
	if (argc > 1)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (pwd_syscall_error(errno));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
