/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:09 by lpin              #+#    #+#             */
/*   Updated: 2023/10/09 16:45:04 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nodo;

	nodo = malloc(sizeof(t_list));
	if (nodo == NULL)
		return (NULL);
	nodo->content = content;
	nodo->next = NULL;
	return (nodo);
}

/*int	main(void)
{
	t_list	*prueba;
	char	c[] = "Hola";

	prueba = ft_lstnew(c);
	printf("El content es: %s\n", prueba->content);
	printf("El next es: %p\n", prueba->next);
	free(prueba);
	return(0);
}*/