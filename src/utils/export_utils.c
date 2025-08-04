/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:33:41 by lucas             #+#    #+#             */
/*   Updated: 2025/08/01 20:45:33 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_utils.h"

void create_default_env(t_env **_env)
{
	char *pwd;
	char *oldpwd;
	int level;
	char *new_shlvl;
	char *pwd_var;
	char *oldpwd_var;

	level = 0;
	new_shlvl = NULL;
	
	// Obtener directorio actual correctamente
	pwd = getcwd(NULL, 0);  // malloc automático
	if (!pwd)
		pwd = ft_strdup("/");  // fallback si getcwd falla
	
	oldpwd = getcwd(NULL, 0);  // otra llamada independiente
	if (!oldpwd)
		oldpwd = ft_strdup("/");  // fallback
	
	// Crear variables de entorno
	lst_add(_env, lst_new(DEFAULT_PATH, false));
	
	pwd_var = ft_strjoin("PWD=", pwd);
	lst_add(_env, lst_new(pwd_var, true));
	free(pwd_var);
	
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	lst_add(_env, lst_new(oldpwd_var, false));
	free(oldpwd_var);
	
	// Manejar SHLVL
	if (find_key(_env, "SHLVL=") != NULL)
	{
		t_env *shlvl = find_key(_env, "SHLVL=");
		level = ft_atoi(shlvl->value) + 1;
		new_shlvl = ft_itoa(level);
		free(shlvl->value);
		shlvl->value = new_shlvl;
	}
	else
		lst_add(_env, lst_new("SHLVL=1", true));
	
	lst_add(_env, lst_new("?=0", false));
	
	// Liberar memoria
	free(pwd);
	free(oldpwd);
}

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
