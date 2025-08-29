/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:39:54 by lpin              #+#    #+#             */
/*   Updated: 2025/08/29 19:54:17 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*change_home(char **args, t_env **_env)
{
	char	*home;

	if (!args || !*_env)
		return (NULL);
	home = home_exists(_env);
	if (!home)
		return (NULL);
	if (!args[1])
		return (ft_strdup(home));
	if (ft_strncmp(args[1], "~/", 2) == 0 && ft_strlen(args[1]) > 1)
		return (ft_strjoin(home, ft_strchr(args[1], '~') + 1));
	else if (ft_strncmp(args[1], "~", 1) == 0)
		return (ft_strdup(home));
	return (NULL);
}

static char	*change_path(int argc, char **args, t_env **_env)
{
	char	*path;
	t_env	*oldpwd_env;

	path = NULL;
	if (argc == 1 || (argc > 1 && args[1] && ft_strncmp(args[1], "~", 1) == 0))
		path = change_home(args, _env);
	else if (argc == 2 && ft_strcmp(args[1], "-") == 0)
	{
		oldpwd_env = find_key(_env, "OLDPWD=");
		path = ft_strdup(oldpwd_env->value);
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

static void	update_path(char *oldpwd, char *new_path, t_env **_env)
{
	char	*aux;

	aux = ft_strjoin_free_s2("OLDPWD=", oldpwd);
	if (update_value(_env, aux) == -1)
		lst_add(_env, lst_new(aux, false));
	ft_destroyer(&aux);
	aux = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
	if (update_value(_env, aux) == -1)
		lst_add(_env, lst_new(aux, false));
	ft_destroyer(&aux);
	ft_destroyer(&new_path);
}

int	built_cd(char **args, t_env **_env)
{
	char	*new_path;
	char	*oldpwd;
	int		argc;
	int		saved;

	argc = args_count(args);
	if (check_cd_error(argc, args, _env) == 1)
		return (1);
	new_path = change_path(argc, args, _env);
	if (!new_path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(new_path) == -1)
	{
		saved = errno;
		cd_syscall_error(new_path, saved);
		return (ft_destroyer(&oldpwd), ft_destroyer(&new_path), 1);
	}
	else
		update_path(oldpwd, new_path, _env);
	return (0);
}
