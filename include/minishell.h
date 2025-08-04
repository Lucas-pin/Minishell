/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:45:07 by manualva          #+#    #+#             */
/*   Updated: 2025/08/01 19:41:22 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <ctype.h>
# include "../include/structs.h"
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# define PROMPT "minishell$ "

# define T_WORD         0
# define T_PIPE         1
# define T_REDIR_IN     2
# define T_REDIR_OUT    3
# define T_HEREDOC      4
# define T_REDIR_APPEND 5
# define FORBIDDEN_CHARS "*;\\&(){}[]`"

//Splits the input line into a linked list of tokens.
t_token		*lexer(char *input);

//Checks if a character is a shell operator.
int			is_operator(char c);

//Checks if a character is a whitespace character.
int			is_space(int c);

//Extracts a word from input, handling quotes and advancing the index.
char		*collect_word(const char *input, int *i, char *quote_type);

//Duplicates a substring from the source string (start, length).
char		*substr_dup(const char *src, int start, int len);

//Compares two strings.
int			ft_strcmp(const char *s1, const char *s2);

//Creates a new token with the given string and type.
t_token		*new_token(char *str, int type);

//Appends a token to the end of a linked list of tokens.
void		add_token(t_token **head, t_token *new_tok);

//Converts a list of tokens into a null-terminated argv array.
char		**token_list_to_argv(t_token *start, t_token *end);

//Frees a linked list of tokens.
void		free_tokens(t_token *tokens);

//Replaces variables in tokens using the provided environment.
void		expander(t_token *tokens, t_env *env);

//Replaces the first variable occurrence in a string with its environment value.
char		*replace_var(const char *input, t_env *env);

//Extracts the variable name from input (starting at index).
char		*get_var_name(const char *input, int start, int *end);

//Builds a new string by replacing the variable reference with its value.
char		*assemble_expanded(const char *input, int var_start, int var_end,
				const char *val);

//Gets the value of an environment variable.
char		*get_env_value(t_env *env, const char *name);

//Parses the list of tokens into a list of commands, split by pipes.
t_cmd		*parser(t_token *tokens);

int			run_heredoc(const char *delimiter);

//Handles I/O redirection for a command based on redirection tokens.
void		handle_redirection(t_token **tokens, t_cmd *cmd);

//Checks for basic syntax errors in the token list.
int			check_syntax(t_token *tokens);

//Checks for unsupported or forbidden characters in a string.
int			contains_forbidden_chars(const char *str);

//Checks special syntax rules (e.g., consecutive operators).
int			check_special_syntax(t_token *tokens);

//Allocates and initializes a new command node.
t_cmd		*init_cmd(void);

//Appends a command node to the end of a linked list.
void		append_cmd(t_cmd **head, t_cmd *new_tok);

//Frees a linked list of commands.
void		free_cmds(t_cmd *cmds);

//Determines the error type and prints an error message.
int			print_error(char *str, int error);

//PARA TESTEAR CON ENVIRONMENTS, BORRAR AL ACABAR DE USARLO
t_env		*new_env(char *key, char *value);
t_env		*mock_env(void);

#endif
