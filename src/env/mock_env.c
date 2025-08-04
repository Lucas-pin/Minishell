/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:23:07 by manualva          #+#    #+#             */
/*   Updated: 2025/08/04 18:11:15 by lpin             ###   ########.fr       */
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
	char 	*key = calloc(5, sizeof(char));
	char 	*value = calloc(20, sizeof(char));
	char	*key_2 = calloc(5, sizeof(char));
	char	*value_2 = calloc(20, sizeof(char));
	t_env 	*env1 = new_env(key, value);
	t_env 	*env2 = new_env(key_2, value_2);

	env1->next = env2;
	return (env1);
}