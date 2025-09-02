/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:56:47 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 11:33:01 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/builtins.h"

static builtin_func	get_builtin_func(const t_builtin cmd)
{
	if (cmd == CD)
		return (built_cd);
	if (cmd == ECHO)
		return (built_echo);
	if (cmd == EXIT)
		return (built_exit);
	if (cmd == PWD)
		return (built_pwd);
	if (cmd == EXPORT)
		return (built_export);
	if (cmd == UNSET)
		return (built_unset);
	if (cmd == ENV)
		return (built_env);
	return (NULL);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	return (-1);
}

static char	**path_cleaner(t_env **env)
{
	t_env	*path_env;
	char	**raw_path;

	path_env = find_key(env, "PATH=");
	if (!path_env || !path_env->value || path_env->value[0] == '\0')
		return (NULL);
	raw_path = ft_split(path_env->value, ':');
	if (!raw_path)
		return (NULL);
	return (raw_path);
}

static char	*get_cmd_path(t_cmd *cmd, char **raw_path)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!cmd || !cmd->cmd)
		return (NULL);
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (access(cmd->cmd, X_OK) == 0)
			return (ft_strdup(cmd->cmd));
		return (NULL);
	}
	if (!raw_path || !*raw_path)
		return (NULL);
	while (*raw_path)
	{
		cmd_path = match_path(cmd, raw_path);
		if (cmd_path)
			return (cmd_path);
		raw_path++;
	}
	return (NULL);
}

t_cmd	*cmd_path(t_cmd *cmd, t_env **env)
{
	char	**raw_path;
	t_cmd	*head;
	int		builtin_index;

	if (!cmd || !env || ft_strcmp(cmd->cmd, "") == 0)
		return (NULL);
	raw_path = path_cleaner(env);
	head = cmd;
	while (cmd)
	{
		builtin_index = is_builtin(cmd->cmd);
		if (builtin_index > -1)
			cmd->cmd_path = (void *)get_builtin_func(builtin_index);
		else
			cmd->cmd_path = (void *)get_cmd_path(cmd, raw_path);
		cmd = cmd->next;
	}
	if (raw_path)
	{
		ft_split_destroyer(raw_path);
		free(raw_path);
	}
	return (head);
}
