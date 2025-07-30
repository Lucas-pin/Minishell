/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:33:41 by lucas             #+#    #+#             */
/*   Updated: 2025/07/30 19:11:28 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

t_env	*find_key(t_env **_env, char *var)
{
	t_env	*aux;
	char	*equal_pos;
	int		key_length;

	if (!var || !*_env)
		return NULL;
	aux = *_env;
	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
		key_length = equal_pos - var;
	else
		key_length = ft_strlen(var);
	while (aux)
	{
		if (ft_strncmp(aux->key, var, key_length) == 0 && 
			aux->key[key_length] == '\0')
			return aux;
		aux = aux->next;
	}
	return NULL;
}

bool exist_key(t_env *_env, char *var)
{
	int		key_length;
	char	*equal_pos;

	if (!var || !_env)
		return (false);
	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
		key_length = equal_pos - var;
	else
		key_length = ft_strlen(var);
	while (_env)
	{
		if (ft_strncmp(_env->key, var, key_length) == 0 && 
			_env->key[key_length] == '\0')
			return (true);
		_env = _env->next;
	}
	return (false);
}

void update_value(t_env **_env, char *var)
{
	t_env	*aux;
	char	*equal_pos;
	int		key_length;

	if (!var || !*_env)
		return ;
	aux = *_env;
	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
		key_length = equal_pos - var;
	else
		key_length = ft_strlen(var);
	while (aux)
	{
		if (ft_strncmp(aux->key, var, key_length) == 0 && 
			aux->key[key_length] == '\0')
		{
			if (aux->value) //Libero el valor si es que tenia
				free(aux->value);
			if (equal_pos) //Actualizo si tiene igual y hago visible el nodo
			{
				aux->value = ft_strdup(equal_pos + 1);
				aux->hide = false;
			}
			else //Sino elimino y oculto el nodo
			{
				aux->value = NULL;
				aux->hide = true;
			}
			return;
		}
		aux = aux->next;
	}
}
