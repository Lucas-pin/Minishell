/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:23:07 by manualva          #+#    #+#             */
/*   Updated: 2025/07/29 09:34:31 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_env	*mock_env(void)
{
	t_env *env1 = new_env("USER", "tester");
	t_env *env2 = new_env("HOME", "/home/tester");

	env1->next = env2;
	return (env1);
}