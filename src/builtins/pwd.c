/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:23:58 by lpin              #+#    #+#             */
/*   Updated: 2025/07/30 20:00:38 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	built_pwd(char **argv, t_env **_env)
{
	char	*cwd;
	int		i;

	i = 0;
	(void)_env;
	if (!argv || ft_strcmp(*argv, "pwd"))
        return (1);
	while (*argv)
	{
		i++;
		argv++;
	}
	if (i > 1)
	{
		ft_putendl_fd("bash: pwd: too many arguments", 2);
		return (1);
	}
    cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}