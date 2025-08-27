/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:00:14 by lpin              #+#    #+#             */
/*   Updated: 2025/08/27 20:44:58 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

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

/* ---- external command error helpers ---- */
static int has_slash(const char *s)
{
	return (s && ft_strchr(s, '/') != NULL);
}

static void print_prefixed_err(const char *cmd, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd && *cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)msg, 2);
}

static void exit_with_exec_error(const char *name, int err, int name_has_slash)
{
	int code;

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
	code = 126;
	exit(code);
}

static void try_exec_or_complain(t_cmd *cmd, t_env **env)
{
	char **envp;
	int err;
	int slash;
	struct stat st;

	slash = has_slash(cmd->cmd);
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

static void	child_process(t_cmd *cmd, t_env **env)
{
	builtin_func	func;
	int			bi;

	if (apply_file_redirs(cmd) == -1)
		exit(1);
	setup_signals_default();
	bi = is_builtin(cmd->cmd);
	if (bi != -1)
	{
		func = (builtin_func)cmd->cmd_path;
		if (func)
			exit(func(cmd->argv, env));
		exit(1);
	}
	try_exec_or_complain(cmd, env);
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
		setup_signals_default();
		try_exec_or_complain(cmd, env);
	}
	setup_signals_parent_wait();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + sig);
	}
	setup_signals_shell();
	return (1);
}

static int	execute_single_cmd(t_cmd *cmd, t_env **env)
{
	int	builtin_index;

	if (!cmd || !env)
		return (-1);
	builtin_index = is_builtin(cmd->cmd);
	if (builtin_index != -1)
		return (run_builtin_parent(cmd, env));
	return (run_external_fork(cmd, env));
}

static int	wait_pipeline(int total, pid_t last_pid)
{
	int		i;
	int		status;
	int		code;
	pid_t	wpid;

	i = 0;
	code = 1;
	setup_signals_parent_wait();
	while (i < total)
	{
		wpid = wait(&status);
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(STDERR_FILENO, "\n", 1);
				else if (sig == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 2);
				code = 128 + sig;
			}
		}
		i++;
	}
	setup_signals_shell();
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
	int	status;

	status = 0;
	if (!cmds || !env)
		return (-1);
	if (!cmds->next)
		status = execute_single_cmd(cmds, env);
	else
		status = execute_multiple_cmds(cmds, env);
	set_last_status(env, status);
	set_exit_status(status);

	return (status);
}
