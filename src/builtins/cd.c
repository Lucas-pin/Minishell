/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:39:54 by lpin              #+#    #+#             */
/*   Updated: 2025/06/26 21:58:24 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

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

int check_argc(char **args)
{
	int i;

	if (!args || !*args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

void    built_cd(t_env **_env, char **args)
{
	char	*path;
	t_env	*pwd_env;
	char	*oldpwd;
	char	**pwd;
	int		argc;

	argc = check_argc(args);
	if (argc < 1 || argc > 2)
		return ;
	if (argc == 1)
	{
		path = home_exists(_env);
		if (!path)
		{
			perror("cd: Error accessing path");
			return ;
		}
	}
	else
		path = args[1];
	oldpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (access(path, F_OK |R_OK | X_OK) == -1 | chdir(path) == -1)
	{
		perror("cd: Error accessing path");
		if (oldpwd)
			free(oldpwd);
		return ;
	}
	else
	{
		update_value(_env, ft_strjoin_free_s2("OLDPWD=", oldpwd));
		update_value(_env, ft_strjoin_free_s2("PWD=", getcwd(NULL, 0)));
	}
}
