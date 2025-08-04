/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:56:55 by manualva          #+#    #+#             */
/*   Updated: 2025/08/04 18:39:03 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/signals.h"
#include "include/builtins_utils.h"
#include "include/executor.h"
#include <stdio.h>

// Print token list for debugging
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%s] Type: %d\n", tokens->str, tokens->type);
		tokens = tokens->next;
	}
}

// Print parsed command structure
void	print_cmds(t_cmd *cmds)
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


int	main(void)
{
	char	input[1024];
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*_env = NULL;

	//_env = mock_env();
	create_default_env(&_env);
	// Setup signal handlers for minishell prompt
	setup_signals_shell();

	while (1)
	{
		printf("minishell> ");
		if (!fgets(input, sizeof(input), stdin))
			break ;

		tokens = lexer(input);
		if (!tokens || !check_special_syntax(tokens))
		{
			free_tokens(tokens);
			continue;
		}

		printf("--- Before Expansion ---\n");
		print_tokens(tokens);

		expander(tokens, _env);
		printf("--- After Expansion ---\n");
		print_tokens(tokens);

		cmds = parser(tokens);
		print_cmds(cmds);
		
		// Iterar sobre la lista enlazada de comandos
		t_cmd *current = cmds;
		while (current)
		{
			if (current->argv && current->argv[0])
			current->cmd = current->argv[0];
			current = current->next;
		}
		
		cmds = cmd_path(cmds, &_env);
		print_cmds(cmds);
		//free_cmds(cmds);
		// TODO: Free cmds here when ready
	}
	lst_free(&_env);
	return (0);
}
