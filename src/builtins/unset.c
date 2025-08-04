/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:35:29 by lpin              #+#    #+#             */
/*   Updated: 2025/08/01 19:46:35 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int built_unset(char **vars, t_env **_env)
{
    t_env	*aux;
	char	*aux_value;

    if (!vars || !*vars || !*_env)
	{
        return (1);
	}
	if (ft_strcmp(*vars, "unset") == 0)
	{
		vars++ ;
	}
    while (*vars)
    {
        aux = *_env;
		aux_value = ft_strchr(*vars, '=');
		if (aux_value)
			aux_value++;
		if (exist_key(aux, *vars))
		{
			aux = find_key(_env, *vars);
			if (!aux_value || ft_strcmp(aux->value, aux_value) == 0)
				remove_node(_env, aux);
		}
        vars++;
    }
	return (0);
}