/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:48:33 by lpin              #+#    #+#             */
/*   Updated: 2025/08/28 21:15:20 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H
# include "../libft/libft.h"
# include "../include/structs.h"
# include <stdbool.h>
# include <errno.h>
# include <string.h>
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
 * @return 0 on success, -1 on failure.
 */
int 	update_value(t_env **_env, char *var);

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

/**
 * @brief Converts the environment linked list to an array of strings.
 * @param env a t_env pointer to the head of the linked list that will store the environment variables.
 * @return an array of strings representing the environment variables in the format "KEY=VALUE".
 * The last element of the array is NULL.
 */
char	**env_to_envp(t_env *env);

/**
 * @brief Converts an array of strings to an environment linked list.
 * @param _env a t_env pointer to the head of the linked list that will store the environment variables.
 * @param envp an array of strings representing the environment variables in the format "KEY=VALUE".
 * @return 0 on success, -1 on failure.
 */
int envp_to_env(t_env **_env, char **envp);


/**
 * @brief Checks if the HOME environment variable exists.
 * @param _env a t_env pointer to the head of the linked list that stores the environment variables.
 * @return the value of the HOME environment variable, or NULL if it does not exist.
 */
char *home_exists(t_env **_env);

/**
 * @brief Checks the arguments and environment for errors in the cd command.
 * @param argc the number of arguments passed to the cd command.
 * @param args an array of strings representing the arguments passed to the cd command.
 * @param _env a t_env pointer to the head of the linked list that stores the environment variables.
 * @return 1 if there is an error, 0 otherwise.
 */
int check_cd_error(int argc, char **args, t_env **_env);

/**
 * @brief Logs an error message for the cd command.
 * @param msg the error message to be logged.
 * @return 1 to indicate an error occurred.
 */
int cd_logical_error(const char *msg);

/**
 * @brief Logs a system call error for the cd command.
 * @param path the path that caused the error.
 * @param saved the saved errno value.
 * @return 1 to indicate an error occurred.
 */
int cd_syscall_error(const char *path, int saved);

/**
 * @brief Counts the number of arguments in a null-terminated array of strings.
 * @param args a null-terminated array of strings.
 * @return the number of arguments in the array.
 */
int args_count(char **args);

/**
 * @brief Validates if a string is a valid shell identifier (until '=' if present).
 * First char: alpha or '_'; subsequent: alnum or '_' up to '=' or end.
 * @param s the string to be validated.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_identifier(const char *s);

/**
 * @brief Like is_valid_identifier, but checks only the first len characters.
 * @param s the string to be validated.
 * @param len the number of characters to check.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_identifier_n(const char *s, int len);

#endif