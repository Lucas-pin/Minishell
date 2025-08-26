/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:09:49 by manualva          #+#    #+#             */
/*   Updated: 2025/08/25 23:52:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

/*Sets up signal handlers for the main shell process.
- SIGINT (Ctrl+C): prints newline, updates exit status to 130.
- SIGQUIT (Ctrl+\): ignored.*/
void	setup_signals_shell(void);

/*Restores default signal behavior. Used for child processes or external 
commands.*/
void	setup_signals_default(void);

// Ignore SIGINT/SIGQUIT in parent while waiting children
void	setup_signals_parent_wait(void);

//Sets the global exit status.
void	set_exit_status(int status);

//Returns the current global exit status.
int		get_exit_status(void);

#endif