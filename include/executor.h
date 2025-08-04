/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:27:21 by lpin              #+#    #+#             */
/*   Updated: 2025/08/01 20:09:17 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../include/structs.h"
# include "../libft/libft.h"
# define DEFAULT_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

/**
 * @brief Gets the command path fot the command list.
 * @param cmd a pointer to the t_cmd structure representing the command.
 * @param env a pointer to the t_env structure representing the environment variables.
 * @return a pointer to the t_cmd structure with the command path set.
 */
t_cmd	*cmd_path(t_cmd *cmd, t_env **env);

#endif
