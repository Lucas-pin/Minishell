/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:56:47 by lpin              #+#    #+#             */
/*   Updated: 2025/07/28 01:31:21 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

char	*builtin_path(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_strdup("../builtins/cd"));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_strdup("../builtins/echo"));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_strdup("../builtins/exit"));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_strdup("../builtins/pwd"));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_strdup("../builtins/export"));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_strdup("../builtins/unset"));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_strdup("../builtins/env"));
	return (NULL);
}

char	**path_cleaner(t_env **env)
{
	t_env	*path_env;
	char	**raw_path;

	path_env = find_key(env, "PATH=");
	if (!path_env)
		return (NULL);
	raw_path = ft_split(path_env->value, ':');
	if (!raw_path)
		return (NULL);
	return (raw_path);
}

char	*get_cmd_path(t_cmd *cmd, char **raw_path)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	if (!cmd || !cmd->cmd || !raw_path || !*raw_path)
		return (NULL);
	if (is_builtin(cmd->cmd))
		return (builtin_path(cmd->cmd));
	while (*raw_path)
	{
		cmd_path = ft_strjoin(*raw_path, "/");
		if (!cmd_path)
			return (NULL);
		cmd_path = ft_strjoin_free_s1(cmd_path, cmd->cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		ft_destroyer(&cmd_path);
		raw_path++;
	}
	return (cmd_path);
}

char	*cmd_path(t_cmd *cmd, t_env **env)
{
	char	**raw_path;
	char	*cmd_path;
	t_cmd	*head;

	if (!cmd || !env || !*env)
		return (NULL);
	raw_path = path_cleaner(env);
	if (!raw_path)
		return (NULL);
	head = cmd;
	while (cmd)
	{
		cmd->cmd_path = get_cmd_path(cmd, &raw_path);
		cmd = cmd->next;
	}
	ft_split_destroyer(&raw_path);
	return (head);
}