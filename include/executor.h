/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:27:21 by lpin              #+#    #+#             */
/*   Updated: 2025/07/05 20:51:15 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# define DEFAULT_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define HASH_SIZE 401 // 401 es primo y es cercano a 400, que es el tamaño máximo esperado de la tabla

typedef struct s_executor
{
	char				**cmd;
	char				*cmd_path;
	int					fd_in;
	int					fd_out;
	struct s_executor	*next;
}	t_executor;

typedef struct s_env
{
	char				*key;
	char				*value;
	unsigned int		hide : 1;	
	struct s_env		*next;
}	t_env;

typedef struct s_hash
{
	t_env			*table[HASH_SIZE];
}	t_hash;

/**
* @brief Initializes the environment variables from the provided array. If the array is NULL, it initializes with a default path.
* @param env An array of strings representing environment variables, typically in the format "KEY=VALUE".
* If NULL, it initializes with a default path.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
*/
void 	built_env(char **env, t_env **_env);

/*
* @brief Creates the default environment variables.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* It initializes the "PATH", "PWD", "OLDPWD", "SHLVL", and "?" variables.
* The "PATH" variable is set to a default value, and "PWD" and "OLDPWD" are set to the current working directory.
* The "SHLVL" variable is initialized to 1, and the "?" variable is set to 0.
* If the "SHLVL" variable already exists, it increments its value by 1
*/
void create_default_env(t_env **_env);

/**
* @brief
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* @param argv an array of strings representing the command line arguments.
* If the first argument is "export", it will add the variables to the environment.
* If the first argument has more than one argument, it will print the environment variables.
* If the first argument is NULL, it will print the environment variables.
*/
void 	built_export(t_env **_env, char **argv);

/**
* @brief create a new list node for the environment variables.
* @param content the content of the new node, typically a string in the format "KEY=VALUE".
* @param visibility a boolean indicating whether the variable is visible or not.
* @return a pointer to the newly created t_env node.
*/
t_env	*lst_new(char *content, bool visibility);

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

/*
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

/*
* @brief Finds a node in the environment linked list by its key.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* @param var a string representing the key of the variable to be found, typically in the format "KEY=VALUE".
* @return a pointer to the t_env node that matches the key, or NULL if not found.
*/
t_env	*find_key(t_env **_env, char *var);

/**
* @brief Unsets (removes) the specified variables from the environment linked list.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* @param vars an array of strings representing the variables to be removed.
* Each string should be the name of the variable to be unset, without the "KEY=VALUE" format.
*/
void	built_unset(t_env **_env, char **vars);

/**
* @brief Changes the current working directory to the specified path.
* @param args an array of strings where the first element is the command (e.g., "cd") and the second element is the path to change to.
* @param _env a t_env pointer to the head of the linked list that will store the environment variables.
* This function updates the "PWD" and "OLDPWD" environment variables accordingly.
* If the path is invalid or the change directory operation fails, it prints an error message.
*/
void	built_cd(t_env **_env, char **args);

/**
 * @brief Prints the arguments to the standard output
 * @param argv an array of strings representing the arguments to be printed.
 * If the first argument is "-n", it prints without a newline at the end.
 * Otherwise, it prints with a newline at the end.
 */

void	built_echo(char **argv);
#endif
