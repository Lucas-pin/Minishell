/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:00:14 by lpin              #+#    #+#             */
/*   Updated: 2025/09/08 22:37:57 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

static void	print_prefixed_err(const char *cmd, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd && *cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)msg, 2);
}

static void	exit_with_exec_error(const char *name, int err, int name_has_slash)
{
	if (!name_has_slash && err == 0)
	{
		print_prefixed_err(name, "command not found");
		exit(127);
	}
	if (err == EACCES)
	{
		print_prefixed_err(name, "Permission denied");
		exit(126);
	}
	if (err == EISDIR)
	{
		print_prefixed_err(name, "Is a directory");
		exit(126);
	}
	if (err == ENOENT)
	{
		print_prefixed_err(name, "No such file or directory");
		exit(127);
	}
	print_prefixed_err(name, (char *)strerror(err));
	exit(126);
}

void	try_exec_or_complain(t_cmd *cmd, t_env **env)
{
	char		**envp;
	int			err;
	int			slash;
	struct stat	st;

	if (ft_strchr(cmd->cmd, '/') != NULL)
		slash = 1;
	if (!cmd->cmd_path || ((char *)cmd->cmd_path)[0] == '\0')
	{
		if (slash)
		{
			if (stat(cmd->cmd, &st) == -1)
				exit_with_exec_error(cmd->cmd, errno, 1);
			if (S_ISDIR(st.st_mode))
				exit_with_exec_error(cmd->cmd, EISDIR, 1);
			if (access(cmd->cmd, X_OK) == -1)
				exit_with_exec_error(cmd->cmd, errno, 1);
		}
		exit_with_exec_error(cmd->cmd, 0, 0);
	}
	envp = env_to_envp(*env);
	execve((char *)cmd->cmd_path, cmd->argv, envp);
	err = errno;
	exit_with_exec_error(cmd->cmd, err, slash);
}

int	executor(t_cmd *cmds, t_env **env)
{
	int	status;

	status = 0;
	if (!cmds || !env)
		return (-1);
	if (!cmds->next)
		status = execute_single_cmd(cmds, env);
	else
		status = execute_multiple_cmds(cmds, env);
	set_exit_status(status);
	setup_signals_shell();
	return (status);
}
