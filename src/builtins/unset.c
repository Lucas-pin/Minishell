/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:35:29 by lpin              #+#    #+#             */
/*   Updated: 2025/05/30 18:40:02 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void built_unset(t_env **_env, char **vars)
{
    t_env	*aux;
	char	*aux_value;

    if (!vars || !*_env)
        return ;
	if (ft_strcmp(*vars, "unset") == 0)
		vars++;
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
}