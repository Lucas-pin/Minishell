/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:54:29 by lpin              #+#    #+#             */
/*   Updated: 2023/10/09 13:20:08 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*int	main(void)
{
	t_list	*prueba;
	t_list	*prueba_2;
	char	c[] = "Hola";
	char	a[] = "Chau";


	prueba = ft_lstnew(c);
	prueba_2 = ft_lstnew(a);
	ft_lstadd_front(&prueba, prueba_2);
	printf("El content es: %s\n", prueba->content);
	prueba = prueba->next;
	printf("El next es: %s\n", prueba->content);
	printf("El next es: %p\n", prueba->next);
	free(prueba);
	free(prueba_2);
	return(0);
}*/