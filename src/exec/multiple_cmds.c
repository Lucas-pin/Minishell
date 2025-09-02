/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:23:03 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 11:01:22 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"

static void	parent_process(int *pipes, pid_t pid, t_cmd_data *data)
{
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	if (data->remaining_cmd > 1)
	{
		close(pipes[1]);
		data->prev_pipe = pipes[0];
	}
	else
		data->last_pid = pid;
}

static int	child_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + sig);
	}
}

static void	child_process(t_cmd *cmd, t_env **env)
{
	builtin_func	func;
	int				bi;

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
			code = child_status(status);
		i++;
	}
	setup_signals_shell();
	return (code);
}

static int	execute_multiple_cmds(t_cmd *cmds, t_env **env)
{
	t_cmd_data	data;
	pid_t		pid;
	int			pipes[2];

	init_cmd_data(cmds, &data);
	while (data.remaining_cmd > 0)
	{
		pipe_creator(pipes, &data);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			pipe_closer(pipes, &data);
			redirect_pipes(pipes, &data);
			child_process(cmds, env);
		}
		parent_process(pipes, pid, &data);
		cmds = cmds->next;
		data.remaining_cmd--;
	}
	if (data.prev_pipe != -1)
		close(data.prev_pipe);
	return (wait_pipeline(data.cmd_qty, data.last_pid));
}
