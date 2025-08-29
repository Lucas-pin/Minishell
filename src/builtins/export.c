/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:03:51 by lpin              #+#    #+#             */
/*   Updated: 2025/08/28 22:28:09 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	print_export(t_env *_env)
{
	if (!_env)
		return ;
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

static void	buble_export(t_env **_env)
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

static int	export_one(t_env **_env, const char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: not a valid identifier: ", 2);
		ft_putendl_fd((char *)arg, 2);
		return (1);
	}
	if (exist_key(*_env, (char *)arg))
		update_value(_env, (char *)arg);
	else if (ft_strchr(arg, '='))
		lst_add(_env, lst_new((char *)arg, false));
	else
		lst_add(_env, lst_new((char *)arg, true));
	return (0);
}

int	built_export(char **args, t_env **_env)
{
	int	arg_count;
	int	has_error;
	int	index;

	if (!args || !*args)
		return (1);
	arg_count = args_count(args);
	if (arg_count == 1)
	{
		buble_export(_env);
		print_export(*_env);
		return (0);
	}
	has_error = 0;
	index = 1;
	while (args[index])
	{
		if (export_one(_env, args[index]) != 0)
			has_error = 1;
		index++;
	}
	return (has_error);
}
