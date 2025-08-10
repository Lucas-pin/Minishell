/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:48:33 by lpin              #+#    #+#             */
/*   Updated: 2025/08/11 00:14:11 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H
# include "../libft/libft.h"
# include "../include/structs.h"
# include <stdbool.h>
# define DEFAULT_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

/**
* @brief create a new list node for the environment variables.
* @param content the content of the new node, typically a string in the format "KEY=VALUE".
* @param visibility a boolean indicating whether the variable is visible or not.
* @return a pointer to the newly created t_env node.
*/
t_env	*lst_new(char *content, bool visibility);

/**
* @brief Frees the memory allocated for the environment linked list.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* This function iterates through the linked list and frees each node's key, value, and the node itself.
*/
void	lst_free(t_env **_env);

/**
* @brief Adds a new variable to the environment linked list.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* @param new_var a pointer to the new t_env node to be added.
*/
void	lst_add(t_env **_env, t_env *new_var);

/**
* @brief Switches the position of the current node with the next node in the linked list until the node is in the correct order.
* @param head a pointer to the head of the linked list.
* @param prev a pointer to the previous node in the linked list.
* @param current a pointer to the current node in the linked list.
* This function is used to sort the linked list of environment variables in alphabetical order.
*/
void	node_switch(t_env **head, t_env *prev, t_env *current);

/**
 * @brief Checks if a variable exists in the environment linked list.
 * @param _env a t_env pointer to the head of the linked list that will store the environment variables.
 * @param var a string representing the variable to be checked, typically in the format "KEY=VALUE".
 * @return true if the variable exists in the linked list, false otherwise.
 */
bool 	exist_key(t_env *_env, char *var);

/**
 * @brief Updates the value of an existing variable in the environment linked list.
 * If the variable exists, it updates its value and visibility. If the variable does not exist, it adds it to the linked list.
 * @param _env a t_env pointer to the head of the linked list that will store the environment variables.
 * @param var a string representing the variable to be updated, typically in the format "KEY=VALUE".
 * If the variable has an equal sign, it updates the value. If it does not have an equal sign, it hides the variable.
 */
void 	update_value(t_env **_env, char *var);

/**
* @brief Removes a node from the environment linked list.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* @param node a pointer to the t_env node to be removed.
*/
void	remove_node(t_env **_env, t_env *node);

/**
 * @brief Finds a node in the environment linked list by its key.
 * @param _env a t_env pointer to the head of the linked list that will store the environment variables.
 * @param var a string representing the key of the variable to be found, typically in the format "KEY=VALUE".
 * @return a pointer to the t_env node that matches the key, or NULL if not found.
 */
t_env	*find_key(t_env **_env, char *var);

/**
 * @brief Checks if the command is a built-in command.
 * @param cmd a string representing the command to be checked.
 * @return an integer representing the built-in command type, or -1 if not a built-in command.
 */
int		is_builtin(const char *cmd);

/*
* @brief Creates the default environment variables.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* It initializes the "PATH", "PWD", "OLDPWD", "SHLVL", and "?" variables.
* The "PATH" variable is set to a default value, and "PWD" and "OLDPWD" are set to the current working directory.
* The "SHLVL" variable is initialized to 1, and the "?" variable is set to 0.
* If the "SHLVL" variable already exists, it increments its value by 1
*/
void 	create_default_env(t_env **_env);

/**
 * @brief Converts the environment linked list to an array of strings.
 * @param env a t_env pointer to the head of the linked list that will store the environment variables.
 * @return an array of strings representing the environment variables in the format "KEY=VALUE".
 * The last element of the array is NULL.
 */
char	**env_to_envp(t_env *env);

#endif