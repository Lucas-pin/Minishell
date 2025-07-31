/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:22:43 by lpin              #+#    #+#             */
/*   Updated: 2023/10/09 18:39:52 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL || del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}

/*void	del(void *s)
{
	while (*(char *)s)
	{
		*(char *)s = 0;
		s++;
	}
}

int	main(void)
{
	t_list	*lst;
	t_list	*node_1;
	char	a[] = "Hola";
	char	b[] = "que";
	char	c[] = "tal";
	char	d[] = "?";
	char	e[] = "Bien";

	lst = ft_lstnew(d);
	node_1 = ft_lstnew(c);
	ft_lstadd_front(&lst, node_1);
	node_1 = ft_lstnew(b);
	ft_lstadd_front(&lst, node_1);
	node_1 = ft_lstnew(a);
	ft_lstadd_front(&lst, node_1);
	node_1 = ft_lstnew(e);
	ft_lstadd_back(&lst, node_1);
	ft_lstdelone(lst, del);
	printf("La direccion de la lista completa es: %p\n", lst);
	while (lst)
	{
		printf("El contenido de la lista completa es: %s\n", lst->content);
		lst = lst->next;
	}
	return (0);
}*/