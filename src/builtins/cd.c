/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:39:54 by lpin              #+#    #+#             */
/*   Updated: 2025/07/27 20:51:21 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static char *home_exists(t_env **_env)
{
	t_env	*home_env;

	if (!_env || !*_env)
		return (NULL);
	home_env = find_key(_env, "HOME=");
	if (home_env && home_env->value)
		return (home_env->value);
	return (NULL);
}

static int go_home(int argc, char **args, t_env **_env)
{
	if (!*_env)
		return (0);
	if (argc == 1)
	{
		if (home_exists(_env))
			return (1);
		else
		{
			perror("cd: HOME not set");
			return (-1);
		}
	}
	if (args[1] && ft_strncmp(args[1], "~", 1) == 0)
	{
		if (home_exists(_env))
			return (1);
		else
		{
			perror("cd: HOME not set");
			return (-1);
		}
	}
	return (0);
}

static char *change_home(t_env **_env, char **args)
{
	char	*home;
	char	*new_path;

	if (!args || !*_env)
		return (NULL);
	if (!args[1])
	{
		home = home_exists(_env);
		if (!home)
			return (NULL);
		new_path = ft_strdup(home);
		return (new_path);
	}
	if (ft_strncmp(args[1], "~/", 2) == 0 && ft_strlen(args[1]) > 1)
	{
		home = home_exists(_env);
		if (!home)
			return (NULL);
		new_path = ft_strjoin(home, ft_strchr(args[1], '~') + 1);
		return (new_path);
	}
	else if (ft_strncmp(args[1], "~", 1) == 0)
	{
		home = home_exists(_env);
		if (!home)
			return (NULL);
		new_path = ft_strdup(home);
		return (new_path);
	}
	return (NULL);
}

static int check_argc(char **args)
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
	char	*oldpwd;
	char	*aux;
	int		argc;

	argc = check_argc(args);
	if (argc < 1 || argc > 2)
		return ;
	if (go_home(argc, args, _env))
	{
		path = change_home(_env, args);
		if (!path)
		{
			perror("cd: HOME not set");
			return ;
		}
	}
	else if (argc = 2 && ft_strcmp(args[1], "-") == 0)
		path = ft_strdup(find_key(_env, "OLDPWD")->value);
	else
		path = ft_strdup(args[1]);
	oldpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (access(path, F_OK |R_OK | X_OK) == -1 | chdir(path) == -1)
	{
		perror("cd: Error accessing path");
		ft_destroyer(&oldpwd);
		ft_destroyer(&path);
		return ;
	}
	else
	{
		aux = ft_strjoin_free_s2("OLDPWD=", oldpwd);
		update_value(_env, aux);
		ft_destroyer(&aux);
		aux = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		update_value(_env, aux);
		ft_destroyer(&aux);
		ft_destroyer(&path);
	}
}
