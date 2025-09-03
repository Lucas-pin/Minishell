/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:00:00 by lpin              #+#    #+#             */
/*   Updated: 2025/09/03 18:58:30 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_utils.h"
#include "../../include/executor.h"

static int	count_visible(t_env *env)
{
	int	cnt;

	cnt = 0;
	while (env)
	{
		if (env->key && env->value && env->hide == 0)
			cnt++;
		env = env->next;
	}
	return (cnt);
}

static char	*join_kv(const char *k, const char *v)
{
	char	*kv;
	char	*tmp;

	tmp = ft_strjoin((char *)k, "=");
	if (!tmp)
		return (NULL);
	kv = ft_strjoin(tmp, (char *)v);
	free(tmp);
	return (kv);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (count_visible(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->key && env->value && env->hide == 0)
		{
			envp[i] = join_kv(env->key, env->value);
			if (!envp[i])
			{
				while (i-- > 0)
					free(envp[i]);
				free(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
