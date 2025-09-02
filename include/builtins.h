/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:27:21 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 11:36:13 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../include/structs.h"
# include "../include/builtins_utils.h"
# include "../libft/libft.h"

/**
* @brief Initializes the environment variables from the provided array. 
* If the array is NULL, it initializes with a default path.
* @param env An array of strings representing environment variables,
* typically in the format "KEY=VALUE".
* If NULL, it initializes with a default path.
* @param _env a t_env pointer to the head of the linked list 
* that will store the environment variables.
*/
int		built_env(char **env, t_env **_env);

/**
* @brief
* @param _env a t_env pointer to the head of the linked list 
* that will store the environment variables.
* @param argv an array of strings representing the command line arguments.
* If the first argument is "export", 
* it will add the variables to the environment.
* If the first argument has more than one argument,
* it will print the environment variables.
* If the first argument is NULL, it will print the environment variables.
*/
int 	built_export(char **args, t_env **_env);

/**
* @brief Unsets (removes) the specified variables from 
* the environment linked list.
* @param _env a t_env pointer to the head of the linked list
* that will store the environment variables.
* @param vars an array of strings representing the variables to be removed.
* Each string should be the name of the variable to be unset,
* without the "KEY=VALUE" format.
*/
int		built_unset(char **args, t_env **_env);

/**
* @brief Changes the current working directory to the specified path.
* @param args an array of strings where the first element is the command 
* (e.g., "cd") and the second element is the path to change to.
* @param _env a t_env pointer to the head of the linked list
* that will store the environment variables.
* This function updates the "PWD" and "OLDPWD" environment variables accordingly.
* If the path is invalid or the change directory operation fails,
* it prints an error message.
*/
int		built_cd(char **args, t_env **_env);

/**
 * @brief Prints the arguments to the standard output
 * @param argv an array of strings representing the arguments to be printed.
 * If the first argument is "-n", it prints without a newline at the end.
 * Otherwise, it prints with a newline at the end.
 */

int		built_echo(char **args, t_env **_env);

/**
 * @brief Terminates the shell with the specified exit status.
 * @param argv an array of strings where the first element is the command
 * (e.g., "exit") and the second element is the exit status.
 * If no arguments are provided, it exits with status 0.
 * If the first argument is "exit", it increments the exit status by 1.
 * If the second argument is not a valid integer, it prints an error message
 * and exits with status 2.
 * If the second argument is a valid integer, it exits with that status.
 */
int		built_exit(char **args, t_env **_env);

/**
 * @brief Prints the current working directory to the standard output.
 * @param argv an array of strings where the first element is the command
 * (e.g., "pwd").
 * If the first argument is not "pwd", it returns 1.
 * Otherwise, it retrieves the current working directory
 * using getcwd and prints it.
 * If getcwd fails, it returns 1.
 */
int		built_pwd(char **args, t_env **_env);

#endif
