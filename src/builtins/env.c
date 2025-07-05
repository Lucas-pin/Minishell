/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:49:34 by lucas             #+#    #+#             */
/*   Updated: 2025/07/05 21:00:27 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void print_env(t_env *_env)
{
	if (!_env)
	return;
	while (_env)
	{
		if (!_env->hide)
		{
			printf("%s", (_env)->key);
			printf("=%s\n", (_env)->value);
		}
		_env = (_env)->next;
	}
}

void create_default_env(t_env **_env)
{
	char *pwd = NULL;
	int level;
	char *new_shlvl;

	level = 0;
	new_shlvl = NULL;
	lst_add(_env, lst_new(DEFAULT_PATH, false));
	lst_add(_env, lst_new(ft_strjoin("PWD=", getcwd(pwd, 1024)), true));
	lst_add(_env, lst_new(ft_strjoin("OLDPWD=", getcwd(pwd, 1024)), false));
	if (find_key(_env, "SHLVL=") != NULL)
	{
		t_env *shlvl = find_key(_env, "SHLVL=");
		level = ft_atoi(shlvl->value) + 1;
		new_shlvl = ft_itoa(level);
		free(shlvl->value);
		shlvl->value = new_shlvl;
	}
	else
		lst_add(_env, lst_new("SHLVL=1", true));
	lst_add(_env, lst_new("?=0", false));
	if (pwd)
		free(pwd);
}

void built_env(char **env, t_env **_env)
{
	while (*env)
	{
		lst_add(_env, lst_new(*env, false));
		env++;
	}
	print_env(*_env);
}
