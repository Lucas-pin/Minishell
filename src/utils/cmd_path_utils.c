/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:25:58 by lpin              #+#    #+#             */
/*   Updated: 2025/09/03 18:59:34 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

char	*match_path(t_cmd *cmd, char **raw_path)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(*raw_path, "/");
	if (!cmd_path)
		return (NULL);
	cmd_path = ft_strjoin_free_s1(cmd_path, cmd->cmd);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	ft_destroyer(&cmd_path);
	return (NULL);
}
