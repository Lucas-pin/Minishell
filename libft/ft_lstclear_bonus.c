/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:13:25 by lpin              #+#    #+#             */
/*   Updated: 2024/06/19 21:22:19 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		aux = (*lst)->next;
		free(*lst);
		*lst = NULL;
		*lst = aux;
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

	lst = ft_lstnew(a);
	node_1 = ft_lstnew(b);
	ft_lstadd_back(&lst, node_1);
	node_1 = ft_lstnew(c);
	ft_lstadd_back(&lst, node_1);
	node_1 = ft_lstnew(d);
	ft_lstadd_back(&lst, node_1);
	node_1 = ft_lstnew(e);
	ft_lstadd_back(&lst, node_1);
	ft_lstclear(&lst, del);
	printf("La direccion de la lista  es: %p\n", lst);
	return (0);
}*/