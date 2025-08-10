/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:39:24 by lpin              #+#    #+#             */
/*   Updated: 2025/08/10 23:53:33 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define HASH_SIZE 401 // 401 es primo y es cercano a 400, que es el tamaño máximo esperado de la tabla

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

#endif
