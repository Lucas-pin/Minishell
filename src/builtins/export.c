/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:03:51 by lpin              #+#    #+#             */
/*   Updated: 2025/05/19 00:34:35 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void print_export(t_env *_env)
{
	if (!_env)
		return;
	while (_env)
	{
		if ((_env)->value != NULL)
		{
			printf("declare -x %s", (_env)->key);
			printf("=\"%s\"\n", (_env)->value);
		}
		else
			printf("declare -x %s\n", (_env)->key);
		_env = (_env)->next;
	}
}


static void buble_export(t_env **_env)
{
	t_env	*aux;
	int		swapped;
	
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		aux = *_env;
		while (aux && aux->next)
		{
			if (ft_strcmp(aux->key, aux->next->key) > 0)
			{
				node_switch(_env, aux, aux->next);
				swapped = 1;
			}
			else
			aux = aux->next;
		}
	}
}

static void add_var(t_env **_env, char **vars)
{
	if (!vars || !*vars)
		return ;
	while (*vars)
	{
		if (ft_strnstr((const char*)*vars, "=", ft_strlen(*vars)))
			lst_add(_env, lst_new(*vars, false));
		else
			lst_add(_env, lst_new(*vars, true));
		vars++;
	}
}

static void modify_vars(t_env **_env, char **vars)
{
	if (!vars || !*vars)
		return ;
	if (ft_strncmp((const char *) *vars, "export", ft_strlen(*vars)) == 0)
		vars ++;
	while (*vars)
	{
		if (exist_key(*_env, *vars))
			update_value(_env, *vars);
		else
			add_var(_env, vars);
		vars++;
	}
}

void built_export(t_env **_env, char **argv)
{
	int		count;
	char	**temp;

	count = 0;
	if (!argv || !*argv)
		return ;
	temp = argv;
	while (*temp)
	{
		count ++;
		temp ++;
	}
	if (count > 1)
	{
		modify_vars(_env, argv);
	}
	else
	{
		buble_export(_env);
		print_export(*_env);
	}
}