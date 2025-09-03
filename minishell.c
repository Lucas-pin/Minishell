/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:56:55 by manualva          #+#    #+#             */
/*   Updated: 2025/09/03 16:49:30 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/builtins_utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*_env;

	(void)argc;
	(void)argv;
	_env = NULL;
	init_env(&_env, envp);
	run_shell(&_env);
	rl_clear_history();
	lst_free(&_env);
	return (0);
}
