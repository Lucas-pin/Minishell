/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:49:34 by lucas             #+#    #+#             */
/*   Updated: 2025/05/18 21:22:56 by lucas            ###   ########.fr       */
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

static void create_default_env(t_env **_env)
{
	char *pwd = NULL;
	lst_add(_env, lst_new(DEFAULT_PATH, false));
	lst_add(_env, lst_new(ft_strjoin("PWD=", getcwd(pwd, 1024)), true));
}

void built_env(char **env, t_env **_env)
{
	if (!*env)
	{
		printf("No hay variables de entorno.\n");
		create_default_env(_env);
	}
	else
	{
		printf("Hay variables de entorno.\n");
		while (*env)
		{
			lst_add(_env, lst_new(*env, false));
			env++;
		}
	}
	print_env(*_env);
}
