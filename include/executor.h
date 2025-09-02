/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:27:21 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 11:33:26 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <string.h>
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
 * @brief Matches the command with its corresponding path in the raw_path array.
 * @param cmd a pointer to the t_cmd structure representing the command.
 * @param raw_path an array of strings representing the raw paths.
 * @return a pointer to the matched command path, or NULL if not found.
 */
char	*match_path(t_cmd *cmd, char **raw_path);

/**
 * @brief Creates pipes for the command execution.
 * @param pipes an array of integers representing the fds for the pipes.
 * @param remaining_cmd the number of remaining commands to be executed.
 * @param cmd_qty the total number of commands in the pipeline.
 * @return a pointer to the pipes array.
 */
int		*pipe_creator(int *pipes, t_cmd_data *data);

/**
 * @brief Redirects the i/o of the current command to the appropriate pipes.
 * @param current_pipe the current pipe file descriptors.
 * @param prev_pipe the previous pipe file descriptor.
 * @param remaining_cmd the number of remaining commands to be executed.
 * @param cmd_qty the total number of commands in the pipeline.
 * @return void
 */
void	redirect_pipes(int *current_pipe, t_cmd_data *data);

/**
 * @brief Closes the pipes used for redirection.
 * @param current_pipe the current pipe file descriptors.
 * @return void
 */
void	pipe_closer(int *current_pipe, t_cmd_data *data);

/**
 * @brief Evaluate how many commands are in the list and execute them.
 * If there is only one command, it executes it directly.
 * If there are multiple cmds, it sets up pipes and executes them in a pipeline.
 * If the command is a built-in, it executes it directly.
 * If the command is not found, it returns an error.
 * @param cmds a pointer to the t_cmd structure representing the command list.
 * @param env a pointer to the t_env representing the environment variables.
 * @return the exit status of the last executed command, or -1 on error.
 */
int		executor(t_cmd *cmds, t_env **env);

/**
 * @brief Initialize the structure to create, redirect and execute each command
 * @param cmds a pointer to the t_cmd structure representigs the command list.
 * @param data a pointer to the t_cmd_data struct representing the command data
 */
void	init_cmd_data(t_cmd *cmds, t_cmd_data *data);

/**
 * @brief Applies files redirections if fd_in/fd_out is != -1
 * @param cmd a pointer to the t_cmd structure representigs the current cmd.
 */
int		apply_file_redirs(t_cmd *cmd);

#endif
