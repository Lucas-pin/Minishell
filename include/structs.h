/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:39:24 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 12:02:06 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <unistd.h>

typedef struct s_env
{
	char				*key;
	char				*value;
	unsigned int		hide : 1;
	struct s_env		*next;
}	t_env;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

typedef int (*builtin_func)(char **, t_env **);

typedef struct s_token
{
	char			*str;
	int				type;
	char			quote_type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	char			*cmd;
	void			*cmd_path;
}	t_cmd;

typedef struct s_cmd_data
{
	int		cmd_qty;
	int		remaining_cmd;
	int		prev_pipe;
	pid_t	last_pid;
}	t_cmd_data;

#endif
