/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:53:07 by lpin              #+#    #+#             */
/*   Updated: 2023/10/20 18:12:35 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	node = lst;
	if (!lst)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

/*int	main(void)
{
	t_list	*lst;
	t_list	*node_1;
	t_list	*last_node;
	char	a[] = "Chau";
	char	b[] = "que";
	char	c[] = "tal";
	char	d[] = "?";

	lst = ft_lstnew(d);
	node_1 = ft_lstnew(c);
	ft_lstadd_front(&lst, node_1);
	node_1 = ft_lstnew(b);
	ft_lstadd_front(&lst, node_1);
	node_1 = ft_lstnew(a);
	ft_lstadd_front(&lst, node_1);
	last_node = ft_lstlast(lst);
	last_node = ft_lstlast(NULL);
	printf("El content de last_node es: %s\n", (char *)last_node->content);
	printf("El next de last_node es: %p\n", last_node->next);
	free(lst);
	return(0);
}
*/