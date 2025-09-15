/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:26:32 by manualva          #+#    #+#             */
/*   Updated: 2025/09/09 18:26:46 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%s] Type: %d\n", tokens->str, tokens->type);
		tokens = tokens->next;
	}
}

static void	print_cmds(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		printf("Command:\n");
		while (cmds->argv && cmds->argv[i])
		{
			printf("  Arg[%d]: %s\n", i, cmds->argv[i]);
			i++;
		}
		printf("  fd_in: %d\n", cmds->fd_in);
		printf("  fd_out: %d\n", cmds->fd_out);
		printf("  cmd: %s\n", cmds->cmd ? cmds->cmd : "NULL");
		if (is_builtin(cmds->cmd) != -1)
			printf("  cmd_path: %p\n", cmds->cmd_path);
		else
			printf("  cmd_path: %s\n", cmds->cmd_path ? (char *)cmds->cmd_path : "NULL");
		cmds = cmds->next;
	}
}
