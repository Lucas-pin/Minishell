/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:00:14 by lpin              #+#    #+#             */
/*   Updated: 2025/08/22 10:04:51 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"
#include "../../include/builtins.h"

static int	set_last_status(t_env **env, int status)
{
	char	*num;
	char	*var;

	if (!env)
		return (-1);
	num = ft_itoa(status);
	if (!num)
		return (-1);
	/* builds "?=N" and frees num */
	var = ft_strjoin_free_s2("?=", num);
	if (!var)
		return (-1);
	update_value(env, var);
	free(var);
	return (0);
}
static int	apply_file_redirs(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	return (0);
}

static void	child_process(t_cmd *cmd, t_env **env)
{
	builtin_func	func;
	int			bi;

	if (apply_file_redirs(cmd) == -1)
		exit(1);
	bi = is_builtin(cmd->cmd);
	if (bi != -1)
	{
		func = (builtin_func)cmd->cmd_path;
		if (func)
			exit(func(cmd->argv, env));
		exit(1);
	}
	if (!cmd->cmd_path || ((char *)cmd->cmd_path)[0] == '\0')
		exit(127);
	execve((char *)cmd->cmd_path, cmd->argv, env_to_envp(*env));
	exit(127);
}

static int	run_builtin_parent(t_cmd *cmd, t_env **env)
{
	int			fd_bkp[2];
	builtin_func	func;
	int			status;

	fd_bkp[0] = dup(STDIN_FILENO);
	fd_bkp[1] = dup(STDOUT_FILENO);
	if (apply_file_redirs(cmd) == -1)
		return (-1);
	func = (builtin_func)cmd->cmd_path;
	status = func(cmd->argv, env);
	dup2(fd_bkp[0], STDIN_FILENO);
	dup2(fd_bkp[1], STDOUT_FILENO);
	close(fd_bkp[0]);
	close(fd_bkp[1]);
	return (status);
}

static int	run_external_fork(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (apply_file_redirs(cmd) == -1)
			exit(1);
		if (!cmd->cmd_path || ((char *)cmd->cmd_path)[0] == '\0')
			exit(127);
		execve((char *)cmd->cmd_path, cmd->argv, env_to_envp(*env));
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	execute_single_cmd(t_cmd *cmd, t_env **env)
{
	int	bi;

	if (!cmd || !env)
		return (-1);
	bi = is_builtin(cmd->cmd);
	if (bi != -1)
		return (run_builtin_parent(cmd, env));
	return (run_external_fork(cmd, env));
}

static int	wait_pipeline(int total, pid_t last_pid)
{
	int		i;
	int		st;
	int		code;
	pid_t	wpid;

	i = 0;
	code = 1;
	while (i < total)
	{
		wpid = wait(&st);
		if (wpid == last_pid)
		{
			if (WIFEXITED(st))
				code = WEXITSTATUS(st);
			else if (WIFSIGNALED(st))
				code = 128 + WTERMSIG(st);
		}
		i++;
	}
	return (code);
}

static int	execute_multiple_cmds(t_cmd *cmds, t_env **env)
{
	pid_t	pid;
	int		cmd_qty;
	int		remaining_cmd;
	int		pipes[2];
	int		prev_pipe;
	pid_t	last_pid;

	cmd_qty = count_cmd(cmds);
	remaining_cmd = cmd_qty;
	prev_pipe = -1;
	last_pid = -1;
	while (remaining_cmd > 0)
	{
		pipe_creator(pipes, remaining_cmd, cmd_qty);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			pipe_closer(pipes, remaining_cmd, cmd_qty);
			redirect_pipes(pipes, prev_pipe, remaining_cmd, cmd_qty);
			child_process(cmds, env);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (remaining_cmd > 1)
		{
			close(pipes[1]);
			prev_pipe = pipes[0];
		}
		else
			last_pid = pid;
		cmds = cmds->next;
		remaining_cmd--;
	}
	if (prev_pipe != -1)
		close(prev_pipe);
	return (wait_pipeline(cmd_qty, last_pid));
}

int	executor(t_cmd *cmds, t_env **env)
{
	int status;

	status = 0;
	if (!cmds || !env)
		return (-1);
	if (!cmds->next)
		status = execute_single_cmd(cmds, env);
	else
		status = execute_multiple_cmds(cmds, env);
	set_last_status(env, status);
	return (status);
}
