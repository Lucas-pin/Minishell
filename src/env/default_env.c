/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:14:13 by lpin              #+#    #+#             */
/*   Updated: 2025/09/03 19:04:24 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	create_default_env(t_env **_env)
{
	char	*pwd;
	char	*oldpwd;
	char	*pwd_var;
	char	*oldpwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("/");
	pwd_var = ft_strjoin_free_s2("PWD=", pwd);
	oldpwd_var = ft_strjoin_free_s2("OLDPWD=", oldpwd);
	lst_add(_env, lst_new(PTH, false));
	lst_add(_env, lst_new(pwd_var, false));
	lst_add(_env, lst_new(oldpwd_var, false));
	lst_add(_env, lst_new("SHLVL=1", false));
	lst_add(_env, lst_new("?=0", true));
	free(pwd_var);
	free(oldpwd_var);
}

static void	bump_shlvl(t_env **_env)
{
	t_env	*var;
	char	*num;
	char	*var_value;
	int		lvl;

	var = find_key(_env, "SHLVL=");
	if (var && var->value)
	{
		lvl = ft_atoi(var->value) + 1;
		num = ft_itoa(lvl);
		if (!num)
			return ;
		var_value = ft_strjoin("SHLVL=", num);
		if (var_value)
		{
			update_value(_env, var_value);
			free(var_value);
		}
		free(num);
	}
}

static void	ensure_question_hidden(t_env **_env)
{
	if (!find_key(_env, "?="))
		lst_add(_env, lst_new("?=0", true));
}

int	envp_to_env(t_env **_env, char **envp)
{
	int	i;

	if (!_env)
		return (-1);
	*_env = NULL;
	if (!envp || !envp[0])
	{
		create_default_env(_env);
		return (0);
	}
	i = 0;
	while (envp[i])
	{
		lst_add(_env, lst_new(envp[i], false));
		i++;
	}
	bump_shlvl(_env);
	ensure_question_hidden(_env);
	return (0);
}
