/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:43:14 by lpin              #+#    #+#             */
/*   Updated: 2023/10/26 16:56:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		*lst = ft_lstlast(*lst);
		(*lst)->next = new;
		*lst = node;
	}
}

/*int	main(void)
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
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	free(lst);
	return (0);
}*/
