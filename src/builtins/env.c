/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:49:34 by lucas             #+#    #+#             */
/*   Updated: 2025/08/01 19:55:19 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int built_env(char **args, t_env **_env)
{
	(void)args;
	t_env *aux;

	if (!_env || !*_env)
		return (1);
	aux = *_env;
	while (aux)
	{
		if (!aux->hide)
		{
			printf("%s", aux->key);
			printf("=%s\n", aux->value);
		}
		aux = aux->next;
	}
	return (0);
}
