/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:27:21 by lpin              #+#    #+#             */
/*   Updated: 2025/08/19 21:50:37 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../include/structs.h"
# include "../libft/libft.h"

/**
 * @brief Gets the command path fot the command list.
 * @param cmd a pointer to the t_cmd structure representing the command.
 * @param env a pointer to the t_env structure representing the environment
 * variables.
 * @return a pointer to the t_cmd structure with the command path set.
 */
t_cmd	*cmd_path(t_cmd *cmd, t_env **env);

/**
 * @brief Creates pipes for the command execution.
 * @param pipes an array of integers representing the file descriptors for the pipes.
 * @param remaining_cmd the number of remaining commands to be executed.
 * @param cmd_qty the total number of commands in the pipeline.
 * @return a pointer to the pipes array.
 */
int	*pipe_creator(int *pipes, int remaining_cmd, int cmq_qty);

/**
 * @brief Redirects the input and output of the current command to the appropriate pipes.
 * @param current_pipe the current pipe file descriptors.
 * @param prev_pipe the previous pipe file descriptor.
 * @param remaining_cmd the number of remaining commands to be executed.
 * @param cmd_qty the total number of commands in the pipeline.
 * @return void
 */
void	redirect_pipes(int *current_pipe, int prev_pipe,
		int remaining_cmd, int cmd_qty);

/**
 * @brief Closes the pipes used for redirection.
 * @param current_pipe the current pipe file descriptors.
 * @return void
 */
void	pipe_closer(int *current_pipe, int remaining_cmd, int cmd_qty);

/**
 * @brief Waits for all child processes to finish.
 * @param remaining_cmd the number of remaining commands to be executed.
 * @return void
 */
void	ft_wait(int remaining_cmd);

/**
 * @brief Evaluate how many commands are in the list and execute them.
 * If there is only one command, it executes it directly.
 * If there are multiple commands, it sets up pipes and executes them in a pipeline.
 * If the command is a built-in, it executes it directly.
 * If the command is not found, it returns an error.
 * @param cmds a pointer to the t_cmd structure representing the command list.
 * @param env a pointer to the t_env structure representing the environment variables.
 * @return the exit status of the last executed command, or -1 on error.
 */
int	executor(t_cmd *cmds, t_env **env);

#endif
