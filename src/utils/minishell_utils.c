/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:44:38 by manualva          #+#    #+#             */
/*   Updated: 2025/09/17 20:00:54 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"
#include "../../include/builtins_utils.h"
#include "../../include/executor.h"

void	init_env(t_env **_env, char **envp)
{
	envp_to_env(_env, envp);
	setup_signals_shell();
}

void	set_cmd_from_argv(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->argv && current->argv[0])
			current->cmd = ft_strdup(current->argv[0]);
		current = current->next;
	}
}

t_cmd	*process_tokens(char *line, t_env **_env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (check_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	expander(tokens, *_env);
	cmds = parser(tokens);
	set_cmd_from_argv(cmds);
	cmds = cmd_path(cmds, _env);
	return (cmds);
}

void	handle_line(char *line, t_env **_env)
{
	t_cmd	*cmds;

	if (!*line)
		return ;
	add_history(line);
	cmds = process_tokens(line, _env);
	if (cmds)
	{
		executor(cmds, _env);
		free_cmds(cmds);
	}
}

void	run_shell(t_env **_env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		handle_line(line, _env);
		free(line);
	}
}
