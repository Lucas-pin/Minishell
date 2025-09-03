/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:34:19 by lpin              #+#    #+#             */
/*   Updated: 2025/09/03 18:59:23 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins_utils.h"

void	remove_node(t_env **_env, t_env *node)
{
	t_env	*aux;

	if (!_env || !*_env || !node)
		return ;
	if (*_env == node)
	{
		*_env = node->next;
		free(node->key);
		free(node->value);
		free(node);
		if (*_env == NULL)
			_env = NULL;
		return ;
	}
	aux = *_env;
	while (aux && aux->next != node)
		aux = aux->next;
	if (aux && aux->next == node)
	{
		aux->next = node->next;
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	node_switch(t_env **head, t_env *first, t_env *second)
{
	t_env	*prev;

	if (!head || !*head || !first || !second || first->next != second)
		return ;
	if (*head == first)
	{
		*head = second;
		first->next = second->next;
		second->next = first;
	}
	else
	{
		prev = *head;
		while (prev && prev->next != first)
			prev = prev->next;
		if (prev)
		{
			prev->next = second;
			first->next = second->next;
			second->next = first;
		}
	}
}

void	lst_add(t_env **_env, t_env *new_var)
{
	t_env	*aux;

	aux = *_env;
	if (new_var == NULL)
		return ;
	if (!_env || !*_env)
		*_env = new_var;
	else
	{
		while ((aux)->next)
			aux = aux->next;
		(aux)->next = new_var;
	}
}

t_env	*lst_new(char *content, bool hide)
{
	t_env	*new_var;
	char	*equal;
	size_t	equal_len;

	equal_len = 0;
	if (content == NULL)
		return (NULL);
	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	memset(new_var, '\0', sizeof(t_env));
	equal = ft_strchr(content, '=');
	if (equal)
	{
		equal_len = equal - content;
		new_var->value = ft_strdup(equal + 1);
		new_var->key = ft_substr(content, 0, equal_len);
	}
	else
		new_var->key = ft_strdup(content);
	new_var->hide = hide;
	new_var->next = NULL;
	return (new_var);
}

void	lst_free(t_env **_env)
{
	t_env	*aux;
	t_env	*next;

	if (!_env || !*_env)
		return ;
	aux = *_env;
	while (aux)
	{
		next = aux->next;
		free(aux->key);
		free(aux->value);
		free(aux);
		aux = next;
	}
	*_env = NULL;
}
