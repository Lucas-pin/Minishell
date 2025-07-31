/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:09:55 by lpin              #+#    #+#             */
/*   Updated: 2023/10/07 19:15:55 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	endl;

	endl = '\n';
	if (fd != -1)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, &endl, 1);
	}
}

/*#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	c[] = "Perrito malvado";

	fd = open("prueba_txt.txt", O_RDWR);
	if (fd != -1)
	{
		ft_putendl_fd(c, fd);
		printf("El fd es: %i", fd);
		close(fd);
	}
	else
		printf("Fallo la apertura");
	return (0);
}*/
//En open utilizo el flag 'O_RDWR' para tener acceso de lectura y escritura
