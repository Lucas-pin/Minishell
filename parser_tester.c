/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:56:55 by manualva          #+#    #+#             */
/*   Updated: 2025/08/28 19:29:08 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/signals.h"
#include "include/builtins_utils.h"
#include "include/executor.h"

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


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*_env = NULL;
	(void)argc; // Unused parameter
	(void)argv; // Unused parameter
	//_env = mock_env();
	envp_to_env(&_env, envp);
	// Setup signal handlers for minishell prompt
	setup_signals_shell();

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);

	tokens = lexer(line);
		if (!tokens)
		{
			free_tokens(tokens);
			free(line);
			continue;
		}

		//printf("--- Before Expansion ---\n");
		//print_tokens(tokens);

		expander(tokens, _env);
		//printf("--- After Expansion ---\n");
		//print_tokens(tokens);

		cmds = parser(tokens);
		//print_cmds(cmds);
		
		// set cmd from argv[0] duplicating to avoid double-free
		t_cmd *current = cmds;
		while (current)
		{
			if (current->argv && current->argv[0])
				current->cmd = ft_strdup(current->argv[0]);
			current = current->next;
		}
		
		cmds = cmd_path(cmds, &_env);
		//print_cmds(cmds);
		
		// execute and show status
		//int status = executor(cmds, &_env);
		//printf("[exec] status=%d\n", status);
		executor(cmds, &_env);
		
		free_cmds(cmds);
		free(line);
	}
	rl_clear_history();
	lst_free(&_env);
	return (0);
}
