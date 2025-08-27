/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:28:34 by manualva          #+#    #+#             */
/*   Updated: 2025/08/27 17:00:36 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

static char	*extract_and_expand(const char *input, int i, int *end, t_env *env)
{
	char	*var;
	char	*val;

	var = get_var_name(input, i, end);
	val = get_env_value(env, var);
	free(var);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static char	*replace_once(char *input, int i, int end, const char *val)
{
	char	*result;

	result = assemble_expanded(input, i, end, val);
	free(input);
	return (result);
}

static char	*expand_variable(char *result, int *i, t_env *env)
{
	char	*val;
	int		end;

	if (result[*i + 1] == '?')
	{
		val = ft_itoa(get_exit_status());
		result = replace_once(result, *i, *i + 2, val);
		*i += ft_strlen(val);
		free(val);
	}
	else if (ft_isalpha(result[*i + 1]))
	{
		val = extract_and_expand(result, *i, &end, env);
		result = replace_once(result, *i, end, val);
		*i += ft_strlen(val);
		free(val);
	}
	else
		(*i)++;
	return (result);
}

char	*replace_var(const char *input, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup(input);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
			result = expand_variable(result, &i, env);
		else
			i++;
	}
	return (result);
}

void	expander(t_token *tokens, t_env *env)
{
	char	*new;

	while (tokens)
	{
		if (tokens->type == T_WORD && tokens->quote_type != '\''
			&& strchr(tokens->str, '$'))
		{
			new = replace_var(tokens->str, env);
			free(tokens->str);
			tokens->str = new;
		}
		tokens = tokens->next;
	}
}
