/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:35:29 by lpin              #+#    #+#             */
/*   Updated: 2025/08/24 20:15:56 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int unset_one(t_env **_env, const char *arg)
{
	const char *eq;
	int         key_len;
	t_env      *node;

	if (!arg)
		return (0);
	if (arg[0] == '-')
	{
		ft_putstr_fd("unset: invalid option -- ", 2);
		ft_putendl_fd((char *)arg, 2);
		return (2);
	}
	eq = ft_strchr(arg, '=');
	key_len = eq ? (int)(eq - arg) : (int)ft_strlen(arg);
	if (!is_valid_identifier_n(arg, key_len))
	{
		ft_putstr_fd("unset: not a valid identifier: ", 2);
		ft_putendl_fd((char *)arg, 2);
		return (1);
	}
	if (!*_env)
		return (0);
	if (exist_key(*_env, (char *)arg))
	{
		node = find_key(_env, (char *)arg);
		if (!eq || (node->value && ft_strcmp(node->value, eq + 1) == 0))
			remove_node(_env, node);
	}
	return (0);
}

int built_unset(char **args, t_env **_env)
{
	int index;
	int saw_ident_err;
	int saw_opt_err;
	int rc;

	if (!args || !*args || !_env)
		return (1);
	index = 1;
	saw_ident_err = 0;
	saw_opt_err = 0;
	while (args[index])
	{
		rc = unset_one(_env, args[index]);
		if (rc == 1)
			saw_ident_err = 1;
		else if (rc == 2)
			saw_opt_err = 1;
		index++;
	}
	if (saw_opt_err)
		return (2);
	if (saw_ident_err)
		return (1);
	return (0);
}