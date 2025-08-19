/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:13:29 by manualva          #+#    #+#             */
/*   Updated: 2025/08/16 22:38:25 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_name(const char *input, int start, int *end)
{
	int	i;

	i = start + 1;
	while (isalnum(input[i]) || input[i] == '_')
		i++;
	*end = i;
	return (substr_dup(input, start + 1, i - start - 1));
}

char	*assemble_expanded(const char *input, int var_start, int var_end,
	const char *val)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*result;

	before = substr_dup(input, 0, var_start);
	after = ft_strdup(&input[var_end]);
	temp = ft_strjoin(before, val);
	result = ft_strjoin(temp, after);
	free(before);
	free(after);
	free(temp);
	return (result);
}

char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
