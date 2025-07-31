/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:56:55 by manualva          #+#    #+#             */
/*   Updated: 2025/07/29 10:11:12 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/signals.h"
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
		cmds = cmds->next;
	}
}


int	main(void)
{
	char	input[1024];
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*env = mock_env();

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

		expander(tokens, env);
		printf("--- After Expansion ---\n");
		print_tokens(tokens);

		cmds = parser(tokens);
		print_cmds(cmds);

		// TODO: Free cmds here when ready
	}
	return (0);
}
