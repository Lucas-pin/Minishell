/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:54:57 by lpin              #+#    #+#             */
/*   Updated: 2025/05/12 20:03:35 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

unsigned int	hash(const char *key)
{
	unsigned int	hash;
	int				i;

	hash = 0;
	i = 0;
	while (key[i])
	{
		hash += key[i];
		i++;
	}
	return (hash % HASH_SIZE);
}

void hash_insert(t_hash *hash_table, const char *key, const char *value)
{
	unsigned int	bucket;
	t_env			*new_node;

	if (!hash_table || !key || !value)
		return ;
	bucket = hash(key);
	new_node = calloc(sizeof(t_env), 1);
	if (!new_node)
		return ;
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->hide = 0;
	new_node->next = NULL;
	if (hash_table->table[bucket] == NULL)
		hash_table->table[bucket] = new_node;
	else
	{
		new_node->next = hash_table->table[bucket];
		hash_table->table[bucket] = new_node;
	}
}
