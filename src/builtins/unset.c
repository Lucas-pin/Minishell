/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:35:29 by lpin              #+#    #+#             */
/*   Updated: 2025/08/29 19:53:07 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	unset_logical_error(const char *msg)
{
	if (msg)
	{
		ft_putstr_fd("unset: ", 2);
		ft_putendl_fd((char *)msg, 2);
	}
	return (1);
}

static int	unset_one(t_env **_env, const char *arg)
{
	const char	*equal_sign_ptr;
	int			key_length;
	t_env		*target_node;

	if (!arg || !*_env)
		return (0);
	if (arg[0] == '-')
		return (unset_logical_error("unset: invalid option -- "), 2);
	equal_sign_ptr = ft_strchr(arg, '=');
	if (equal_sign_ptr)
		key_length = (int)(equal_sign_ptr - arg);
	else
		key_length = (int)ft_strlen(arg);
	if (!is_valid_identifier_n(arg, key_length))
		return (unset_logical_error("unset: not a valid identifier: "), 1);
	target_node = find_key(_env, (char *)arg);
	if (target_node && (!equal_sign_ptr || (target_node->value
				&& ft_strcmp(target_node->value, equal_sign_ptr + 1) == 0)))
		remove_node(_env, target_node);
	return (0);
}

int	built_unset(char **args, t_env **_env)
{
	int		arg_index;
	int		result_code;
	int		final_error;

	if (!_env || !args || !*args)
		return (1);
	arg_index = 1;
	final_error = 0;
	while (args[arg_index])
	{
		result_code = unset_one(_env, args[arg_index]);
		if (result_code == 2)
			final_error = 2;
		else if (result_code == 1 && final_error == 0)
			final_error = 1;
		arg_index++;
	}
	return (final_error);
}
