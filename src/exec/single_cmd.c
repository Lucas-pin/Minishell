/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:10:12 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 19:27:45 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/minishell.h"
#include "../../include/signals.h"
#include "../../include/builtins.h"

static void	child_process(t_cmd *cmd, t_env **env)
{
	if (apply_file_redirs(cmd) == -1)
		exit(1);
	setup_signals_default();
	try_exec_or_complain(cmd, env);
}

static int	run_external_fork(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;
	int		sig;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		child_process(cmd, env);
	setup_signals_parent_wait();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + sig);
	}
	setup_signals_shell();
	return (1);
}

static int	run_builtin_parent(t_cmd *cmd, t_env **env)
{
	int	fd_bkp[2];
	int	(*func)(char **, t_env **);
	int	status;

	fd_bkp[0] = dup(STDIN_FILENO);
	fd_bkp[1] = dup(STDOUT_FILENO);
	if (apply_file_redirs(cmd) == -1)
		return (-1);
	func = (int (*)(char **, t_env **))cmd->cmd_path;
	status = func(cmd->argv, env);
	dup2(fd_bkp[0], STDIN_FILENO);
	dup2(fd_bkp[1], STDOUT_FILENO);
	close(fd_bkp[0]);
	close(fd_bkp[1]);
	return (status);
}

int	execute_single_cmd(t_cmd *cmd, t_env **env)
{
	int	builtin_index;

	if (!cmd || !env)
		return (-1);
	builtin_index = is_builtin(cmd->cmd);
	if (builtin_index != -1)
		return (run_builtin_parent(cmd, env));
	return (run_external_fork(cmd, env));
}
